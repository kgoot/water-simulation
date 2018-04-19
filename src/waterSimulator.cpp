#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <CGL/vector3D.h>
#include <nanogui/nanogui.h>

#include "waterSimulator.h"

#include "camera.h"
#include "water.h"
#include "collision/plane.h"
#include "collision/sphere.h"
#include "misc/camera_info.h"
#include "container.h"

using namespace nanogui;
using namespace std;

WaterSimulator::WaterSimulator(Screen *screen) {
  this->screen = screen;

  // Initialize OpenGL buffers and shaders

  wireframeShader.initFromFiles("Wireframe", "../shaders/camera.vert",
                                "../shaders/wireframe.frag");
  normalShader.initFromFiles("Normal", "../shaders/camera.vert",
                             "../shaders/normal.frag");
  phongShader.initFromFiles("Phong", "../shaders/camera.vert",
                            "../shaders/phong.frag");

  shaders.push_back(wireframeShader);
  shaders.push_back(normalShader);
  shaders.push_back(phongShader);

  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_DEPTH_TEST);
}

WaterSimulator::~WaterSimulator() {
  for (auto shader : shaders) {
    shader.free();
  }

  if (cloth) delete cloth;
  if (cp) delete cp;
  if (collision_objects) delete collision_objects;
}

void WaterSimulator::loadCloth(Water *cloth) { this->cloth = cloth; }

void WaterSimulator::loadClothParameters(WaterParameters *cp) { this->cp = cp; }

void WaterSimulator::loadCollisionObjects(vector<CollisionObject *> *objects) { this->collision_objects = objects; }

/**
 * Initializes the cloth simulation and spawns a new thread to separate
 * rendering from simulation.
 */
void WaterSimulator::init() {
  // Initialize GUI
  initGUI(screen);
  screen->setSize(default_window_size);

  // Initialize camera

  CGL::Collada::CameraInfo camera_info;
  camera_info.hFov = 50;
  camera_info.vFov = 35;
  camera_info.nClip = 0.01;
  camera_info.fClip = 10000;

  // Try to intelligently figure out the camera target

  Vector3D avg_pm_position(0, 0, 0);

  for (auto &pm : cloth->point_masses) {
    avg_pm_position += pm.position / cloth->point_masses.size();
  }

  CGL::Vector3D target(avg_pm_position.x, avg_pm_position.y / 2,
                       avg_pm_position.z);
  CGL::Vector3D c_dir(0., 0., 0.);
  canonical_view_distance = max(cloth->width, cloth->height) * 0.9;
  scroll_rate = canonical_view_distance / 10;

  view_distance = canonical_view_distance * 2;
  min_view_distance = canonical_view_distance / 10.0;
  max_view_distance = canonical_view_distance * 20.0;

  // canonicalCamera is a copy used for view resets

  camera.place(target, acos(c_dir.y), atan2(c_dir.x, c_dir.z), view_distance,
               min_view_distance, max_view_distance);
  canonicalCamera.place(target, acos(c_dir.y), atan2(c_dir.x, c_dir.z),
                        view_distance, min_view_distance, max_view_distance);

  screen_w = default_window_size(0);
  screen_h = default_window_size(1);

  camera.configure(camera_info, screen_w, screen_h);
  canonicalCamera.configure(camera_info, screen_w, screen_h);
}

bool WaterSimulator::isAlive() { return is_alive; }

void WaterSimulator::drawContents() {
  glEnable(GL_DEPTH_TEST);

  // Bind the active shader

  GLShader shader = shaders[activeShader];
  shader.bind();

  // Prepare the camera projection matrix

  Matrix4f model;
  model.setIdentity();

  Matrix4f view = getViewMatrix();
  Matrix4f projection = getProjectionMatrix();

  Matrix4f viewProjection = projection * view;

  shader.setUniform("model", model);
  shader.setUniform("viewProjection", viewProjection);

  switch (activeShader) {
  case WIREFRAME:
    drawWireframe(shader);
    break;
  case NORMALS:
    drawNormals(shader);
    break;
  case PHONG:
    drawPhong(shader);
    break;
  }

  for (CollisionObject *co : *collision_objects) {
    co->render(shader);
  }
}

void WaterSimulator::drawWireframe(GLShader &shader) {
  int num_structural_springs =
      2 * cloth->num_width_points * cloth->num_height_points -
      cloth->num_width_points - cloth->num_height_points;
  int num_shear_springs =
      2 * (cloth->num_width_points - 1) * (cloth->num_height_points - 1);
  int num_bending_springs = num_structural_springs - cloth->num_width_points -
                            cloth->num_height_points;

  int num_springs = cp->enable_structural_constraints * num_structural_springs +
                    cp->enable_shearing_constraints * num_shear_springs +
                    cp->enable_bending_constraints * num_bending_springs;

  MatrixXf positions(3, num_springs * 2);
  MatrixXf normals(3, num_springs * 2);

  // Draw springs as lines

  int si = 0;

  for (int i = 0; i < cloth->springs.size(); i++) {
    Spring s = cloth->springs[i];

    if ((s.spring_type == STRUCTURAL && !cp->enable_structural_constraints) ||
        (s.spring_type == SHEARING && !cp->enable_shearing_constraints) ||
        (s.spring_type == BENDING && !cp->enable_bending_constraints)) {
      continue;
    }

    Vector3D pa = s.pm_a->position;
    Vector3D pb = s.pm_b->position;

    Vector3D na = s.pm_a->normal();
    Vector3D nb = s.pm_b->normal();

    positions.col(si) << pa.x, pa.y, pa.z;
    positions.col(si + 1) << pb.x, pb.y, pb.z;

    normals.col(si) << na.x, na.y, na.z;
    normals.col(si + 1) << nb.x, nb.y, nb.z;

    si += 2;
  }

  shader.setUniform("in_color", nanogui::Color(1.0f, 1.0f, 1.0f, 1.0f));
  shader.uploadAttrib("in_position", positions);
  shader.drawArray(GL_LINES, 0, num_springs * 2);


  // Initialise GLFW
//  if( !glfwInit() )
//  {
//    fprintf( stderr, "Failed to initialize GLFW\n" );
//    getchar();
//    return -1;
//  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  GLFWwindow* window = glfwCreateWindow( 1024, 768, "Tutorial 04 - Colored Cube", NULL, NULL);
  if( window == NULL ){
    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
    getchar();
    glfwTerminate();
//    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return -1;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  // Create and compile our GLSL program from the shaders
  GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

  // Get a handle for our "MVP" uniform
  GLuint MatrixID = glGetUniformLocation(programID, "MVP");

  // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
  // Camera matrix
  glm::mat4 View       = glm::lookAt(
      glm::vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
      glm::vec3(0,0,0), // and looks at the origin
      glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
  );
  // Model matrix : an identity matrix (model will be at the origin)
  glm::mat4 Model      = glm::mat4(1.0f);
  // Our ModelViewProjection : multiplication of our 3 matrices
  glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

  // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
  // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
  static const GLfloat g_vertex_buffer_data[] = {
      -1.0f,-1.0f,-1.0f,
      -1.0f,-1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f,
      1.0f, 1.0f,-1.0f,
      -1.0f,-1.0f,-1.0f,
      -1.0f, 1.0f,-1.0f,
      1.0f,-1.0f, 1.0f,
      -1.0f,-1.0f,-1.0f,
      1.0f,-1.0f,-1.0f,
      1.0f, 1.0f,-1.0f,
      1.0f,-1.0f,-1.0f,
      -1.0f,-1.0f,-1.0f,
      -1.0f,-1.0f,-1.0f,
      -1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f,-1.0f,
      1.0f,-1.0f, 1.0f,
      -1.0f,-1.0f, 1.0f,
      -1.0f,-1.0f,-1.0f,
      -1.0f, 1.0f, 1.0f,
      -1.0f,-1.0f, 1.0f,
      1.0f,-1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f,-1.0f,-1.0f,
      1.0f, 1.0f,-1.0f,
      1.0f,-1.0f,-1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f,-1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f,-1.0f,
      -1.0f, 1.0f,-1.0f,
      1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f,-1.0f,
      -1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f,
      1.0f,-1.0f, 1.0f
  };

  // One color for each vertex. They were generated randomly.
  static const GLfloat g_color_buffer_data[] = {
      0.583f,  0.771f,  0.014f,
      0.609f,  0.115f,  0.436f,
      0.327f,  0.483f,  0.844f,
      0.822f,  0.569f,  0.201f,
      0.435f,  0.602f,  0.223f,
      0.310f,  0.747f,  0.185f,
      0.597f,  0.770f,  0.761f,
      0.559f,  0.436f,  0.730f,
      0.359f,  0.583f,  0.152f,
      0.483f,  0.596f,  0.789f,
      0.559f,  0.861f,  0.639f,
      0.195f,  0.548f,  0.859f,
      0.014f,  0.184f,  0.576f,
      0.771f,  0.328f,  0.970f,
      0.406f,  0.615f,  0.116f,
      0.676f,  0.977f,  0.133f,
      0.971f,  0.572f,  0.833f,
      0.140f,  0.616f,  0.489f,
      0.997f,  0.513f,  0.064f,
      0.945f,  0.719f,  0.592f,
      0.543f,  0.021f,  0.978f,
      0.279f,  0.317f,  0.505f,
      0.167f,  0.620f,  0.077f,
      0.347f,  0.857f,  0.137f,
      0.055f,  0.953f,  0.042f,
      0.714f,  0.505f,  0.345f,
      0.783f,  0.290f,  0.734f,
      0.722f,  0.645f,  0.174f,
      0.302f,  0.455f,  0.848f,
      0.225f,  0.587f,  0.040f,
      0.517f,  0.713f,  0.338f,
      0.053f,  0.959f,  0.120f,
      0.393f,  0.621f,  0.362f,
      0.673f,  0.211f,  0.457f,
      0.820f,  0.883f,  0.371f,
      0.982f,  0.099f,  0.879f
  };

  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  GLuint colorbuffer;
  glGenBuffers(1, &colorbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

  do{

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(programID);

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        3,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  } // Check if the ESC key was pressed or the window was closed
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0 );

  // Cleanup VBO and shader
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteBuffers(1, &colorbuffer);
  glDeleteProgram(programID);
  glDeleteVertexArrays(1, &VertexArrayID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

//  return 0;
}

void WaterSimulator::drawNormals(GLShader &shader) {
  int num_tris = cloth->clothMesh->triangles.size();

  MatrixXf positions(3, num_tris * 3);
  MatrixXf normals(3, num_tris * 3);

  for (int i = 0; i < num_tris; i++) {
    Triangle *tri = cloth->clothMesh->triangles[i];

    Vector3D p1 = tri->pm1->position;
    Vector3D p2 = tri->pm2->position;
    Vector3D p3 = tri->pm3->position;

    Vector3D n1 = tri->pm1->normal();
    Vector3D n2 = tri->pm2->normal();
    Vector3D n3 = tri->pm3->normal();

    positions.col(i * 3) << p1.x, p1.y, p1.z;
    positions.col(i * 3 + 1) << p2.x, p2.y, p2.z;
    positions.col(i * 3 + 2) << p3.x, p3.y, p3.z;

    normals.col(i * 3) << n1.x, n1.y, n1.z;
    normals.col(i * 3 + 1) << n2.x, n2.y, n2.z;
    normals.col(i * 3 + 2) << n3.x, n3.y, n3.z;
  }

  shader.uploadAttrib("in_position", positions);
  shader.uploadAttrib("in_normal", normals);

  shader.drawArray(GL_TRIANGLES, 0, num_tris * 3);
}

void WaterSimulator::drawPhong(GLShader &shader) {
  int num_tris = cloth->clothMesh->triangles.size();

  MatrixXf positions(3, num_tris * 3);
  MatrixXf normals(3, num_tris * 3);

  for (int i = 0; i < num_tris; i++) {
    Triangle *tri = cloth->clothMesh->triangles[i];

    Vector3D p1 = tri->pm1->position;
    Vector3D p2 = tri->pm2->position;
    Vector3D p3 = tri->pm3->position;

    Vector3D n1 = tri->pm1->normal();
    Vector3D n2 = tri->pm2->normal();
    Vector3D n3 = tri->pm3->normal();

    positions.col(i * 3) << p1.x, p1.y, p1.z;
    positions.col(i * 3 + 1) << p2.x, p2.y, p2.z;
    positions.col(i * 3 + 2) << p3.x, p3.y, p3.z;

    normals.col(i * 3) << n1.x, n1.y, n1.z;
    normals.col(i * 3 + 1) << n2.x, n2.y, n2.z;
    normals.col(i * 3 + 2) << n3.x, n3.y, n3.z;
  }

  Vector3D cp = camera.position();

  shader.setUniform("in_color", color);
  shader.setUniform("eye", Vector3f(cp.x, cp.y, cp.z));
  shader.setUniform("light", Vector3f(0.5, 2, 2));

  shader.uploadAttrib("in_position", positions);
  shader.uploadAttrib("in_normal", normals);

  shader.drawArray(GL_TRIANGLES, 0, num_tris * 3);
}

// ----------------------------------------------------------------------------
// CAMERA CALCULATIONS
//
// OpenGL 3.1 deprecated the fixed pipeline, so we lose a lot of useful OpenGL
// functions that have to be recreated here.
// ----------------------------------------------------------------------------

void WaterSimulator::resetCamera() { camera.copy_placement(canonicalCamera); }

Matrix4f WaterSimulator::getProjectionMatrix() {
  Matrix4f perspective;
  perspective.setZero();

  double near = camera.near_clip();
  double far = camera.far_clip();

  double theta = camera.v_fov() * M_PI / 360;
  double range = far - near;
  double invtan = 1. / tanf(theta);

  perspective(0, 0) = invtan / camera.aspect_ratio();
  perspective(1, 1) = invtan;
  perspective(2, 2) = -(near + far) / range;
  perspective(3, 2) = -1;
  perspective(2, 3) = -2 * near * far / range;
  perspective(3, 3) = 0;

  return perspective;
}

Matrix4f WaterSimulator::getViewMatrix() {
  Matrix4f lookAt;
  Matrix3f R;

  lookAt.setZero();

  // Convert CGL vectors to Eigen vectors
  // TODO: Find a better way to do this!

  CGL::Vector3D c_pos = camera.position();
  CGL::Vector3D c_udir = camera.up_dir();
  CGL::Vector3D c_target = camera.view_point();

  Vector3f eye(c_pos.x, c_pos.y, c_pos.z);
  Vector3f up(c_udir.x, c_udir.y, c_udir.z);
  Vector3f target(c_target.x, c_target.y, c_target.z);

  R.col(2) = (eye - target).normalized();
  R.col(0) = up.cross(R.col(2)).normalized();
  R.col(1) = R.col(2).cross(R.col(0));

  lookAt.topLeftCorner<3, 3>() = R.transpose();
  lookAt.topRightCorner<3, 1>() = -R.transpose() * eye;
  lookAt(3, 3) = 1.0f;

  return lookAt;
}

// ----------------------------------------------------------------------------
// EVENT HANDLING
// ----------------------------------------------------------------------------

bool WaterSimulator::cursorPosCallbackEvent(double x, double y) {
  if (left_down && !middle_down && !right_down) {
    if (ctrl_down) {
      mouseRightDragged(x, y);
    } else {
      mouseLeftDragged(x, y);
    }
  } else if (!left_down && !middle_down && right_down) {
    mouseRightDragged(x, y);
  } else if (!left_down && !middle_down && !right_down) {
    mouseMoved(x, y);
  }

  mouse_x = x;
  mouse_y = y;

  return true;
}

bool WaterSimulator::mouseButtonCallbackEvent(int button, int action,
                                              int modifiers) {
  switch (action) {
  case GLFW_PRESS:
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
      left_down = true;
      break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
      middle_down = true;
      break;
    case GLFW_MOUSE_BUTTON_RIGHT:
      right_down = true;
      break;
    }
    return true;

  case GLFW_RELEASE:
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
      left_down = false;
      break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
      middle_down = false;
      break;
    case GLFW_MOUSE_BUTTON_RIGHT:
      right_down = false;
      break;
    }
    return true;
  }

  return false;
}

void WaterSimulator::mouseMoved(double x, double y) { y = screen_h - y; }

void WaterSimulator::mouseLeftDragged(double x, double y) {
  float dx = x - mouse_x;
  float dy = y - mouse_y;

  camera.rotate_by(-dy * (PI / screen_h), -dx * (PI / screen_w));
}

void WaterSimulator::mouseRightDragged(double x, double y) {
  camera.move_by(mouse_x - x, y - mouse_y, canonical_view_distance);
}

bool WaterSimulator::keyCallbackEvent(int key, int scancode, int action,
                                      int mods) {
  ctrl_down = (bool)(mods & GLFW_MOD_CONTROL);

  if (action == GLFW_PRESS) {
    switch (key) {
    case GLFW_KEY_ESCAPE:
      is_alive = false;
      break;
    case 'r':
    case 'R':
      cloth->reset();
      break;
    case ' ':
      resetCamera();
      break;
    case 'p':
    case 'P':
      is_paused = !is_paused;
      break;
    case 'n':
    case 'N':
      if (is_paused) {
        is_paused = false;
        drawContents();
        is_paused = true;
      }
      break;
    }
  }

  return true;
}

bool WaterSimulator::dropCallbackEvent(int count, const char **filenames) {
  return true;
}

bool WaterSimulator::scrollCallbackEvent(double x, double y) {
  camera.move_forward(y * scroll_rate);
  return true;
}

bool WaterSimulator::resizeCallbackEvent(int width, int height) {
  screen_w = width;
  screen_h = height;

  camera.set_screen_size(screen_w, screen_h);
  return true;
}

void WaterSimulator::initGUI(Screen *screen) {
  Window *window = new Window(screen, "Settings");
  window->setPosition(Vector2i(15, 15));
  window->setLayout(new GroupLayout(15, 6, 14, 5));

  // Spring types

  new Label(window, "Spring types", "sans-bold");

  {
    Button *b = new Button(window, "structural");
    b->setFlags(Button::ToggleButton);
    b->setPushed(cp->enable_structural_constraints);
    b->setFontSize(14);
    b->setChangeCallback(
        [this](bool state) { cp->enable_structural_constraints = state; });

    b = new Button(window, "shearing");
    b->setFlags(Button::ToggleButton);
    b->setPushed(cp->enable_shearing_constraints);
    b->setFontSize(14);
    b->setChangeCallback(
        [this](bool state) { cp->enable_shearing_constraints = state; });

    b = new Button(window, "bending");
    b->setFlags(Button::ToggleButton);
    b->setPushed(cp->enable_bending_constraints);
    b->setFontSize(14);
    b->setChangeCallback(
        [this](bool state) { cp->enable_bending_constraints = state; });
  }

  // Mass-spring parameters

  new Label(window, "Parameters", "sans-bold");

  {
    Widget *panel = new Widget(window);
    GridLayout *layout =
        new GridLayout(Orientation::Horizontal, 2, Alignment::Middle, 5, 5);
    layout->setColAlignment({Alignment::Maximum, Alignment::Fill});
    layout->setSpacing(0, 10);
    panel->setLayout(layout);

    new Label(panel, "density :", "sans-bold");

    FloatBox<double> *fb = new FloatBox<double>(panel);
    fb->setEditable(true);
    fb->setFixedSize(Vector2i(100, 20));
    fb->setFontSize(14);
    fb->setValue(cp->density / 10);
    fb->setUnits("g/cm^2");
    fb->setSpinnable(true);
    fb->setCallback([this](float value) { cp->density = (double)(value * 10); });

    new Label(panel, "ks :", "sans-bold");

    fb = new FloatBox<double>(panel);
    fb->setEditable(true);
    fb->setFixedSize(Vector2i(100, 20));
    fb->setFontSize(14);
    fb->setValue(cp->ks);
    fb->setUnits("N/m");
    fb->setSpinnable(true);
    fb->setMinValue(0);
    fb->setCallback([this](float value) { cp->ks = value; });
  }

  // Simulation constants

  new Label(window, "Simulation", "sans-bold");

  {
    Widget *panel = new Widget(window);
    GridLayout *layout =
        new GridLayout(Orientation::Horizontal, 2, Alignment::Middle, 5, 5);
    layout->setColAlignment({Alignment::Maximum, Alignment::Fill});
    layout->setSpacing(0, 10);
    panel->setLayout(layout);

    new Label(panel, "frames/s :", "sans-bold");

    IntBox<int> *fsec = new IntBox<int>(panel);
    fsec->setEditable(true);
    fsec->setFixedSize(Vector2i(100, 20));
    fsec->setFontSize(14);
    fsec->setValue(frames_per_sec);
    fsec->setSpinnable(true);
    fsec->setCallback([this](int value) { frames_per_sec = value; });

    new Label(panel, "steps/frame :", "sans-bold");

    IntBox<int> *num_steps = new IntBox<int>(panel);
    num_steps->setEditable(true);
    num_steps->setFixedSize(Vector2i(100, 20));
    num_steps->setFontSize(14);
    num_steps->setValue(simulation_steps);
    num_steps->setSpinnable(true);
    num_steps->setMinValue(0);
    num_steps->setCallback([this](int value) { simulation_steps = value; });
  }

  // Damping slider and textbox

  new Label(window, "Damping", "sans-bold");

  {
    Widget *panel = new Widget(window);
    panel->setLayout(
        new BoxLayout(Orientation::Horizontal, Alignment::Middle, 0, 5));

    Slider *slider = new Slider(panel);
    slider->setValue(cp->damping);
    slider->setFixedWidth(105);

    TextBox *percentage = new TextBox(panel);
    percentage->setFixedWidth(75);
    percentage->setValue(to_string(cp->damping));
    percentage->setUnits("%");
    percentage->setFontSize(14);

    slider->setCallback([percentage](float value) {
      percentage->setValue(std::to_string(value));
    });
    slider->setFinalCallback([&](float value) {
      cp->damping = (double)value;
      // cout << "Final slider value: " << (int)(value * 100) << endl;
    });
  }

  // Gravity

  new Label(window, "Gravity", "sans-bold");

  {
    Widget *panel = new Widget(window);
    GridLayout *layout =
        new GridLayout(Orientation::Horizontal, 2, Alignment::Middle, 5, 5);
    layout->setColAlignment({Alignment::Maximum, Alignment::Fill});
    layout->setSpacing(0, 10);
    panel->setLayout(layout);

    new Label(panel, "x :", "sans-bold");

    FloatBox<double> *fb = new FloatBox<double>(panel);
    fb->setEditable(true);
    fb->setFixedSize(Vector2i(100, 20));
    fb->setFontSize(14);
    fb->setValue(gravity.x);
    fb->setUnits("m/s^2");
    fb->setSpinnable(true);
    fb->setCallback([this](float value) { gravity.x = value; });

    new Label(panel, "y :", "sans-bold");

    fb = new FloatBox<double>(panel);
    fb->setEditable(true);
    fb->setFixedSize(Vector2i(100, 20));
    fb->setFontSize(14);
    fb->setValue(gravity.y);
    fb->setUnits("m/s^2");
    fb->setSpinnable(true);
    fb->setCallback([this](float value) { gravity.y = value; });

    new Label(panel, "z :", "sans-bold");

    fb = new FloatBox<double>(panel);
    fb->setEditable(true);
    fb->setFixedSize(Vector2i(100, 20));
    fb->setFontSize(14);
    fb->setValue(gravity.z);
    fb->setUnits("m/s^2");
    fb->setSpinnable(true);
    fb->setCallback([this](float value) { gravity.z = value; });
  }

  // Appearance

  new Label(window, "Appearance", "sans-bold");

  {
    ComboBox *cb = new ComboBox(window, {"Wireframe", "Normals", "Shaded"});
    cb->setFontSize(14);
    cb->setCallback(
        [this, screen](int idx) { activeShader = static_cast<e_shader>(idx); });
  }

  new Label(window, "Color", "sans-bold");

  {
    ColorWheel *cw = new ColorWheel(window, color);
    cw->setCallback(
        [this](const nanogui::Color &color) { this->color = color; });
  }
}
