set(SOURCE_FILES
        main.cpp
        core/app.cpp
        scene/thing.cpp
        ../deps/glad/src/glad.c)

set(HEADER_FILES
        core/app.h
        scene/thing.h core/input.h core/view.cpp core/view.h core/renderer.cpp core/renderer.h core/config.h core/state.h states/view-state.cpp states/view-state.h pbf/pbf.cpp pbf/pbf.h pbf/particle.h pbf/kernels.h scene/camera.cpp scene/camera.cpp scene/camera.h scene/scene.cpp scene/scene.h pbf/particles.cpp pbf/particles.h gl/shader.cpp gl/shader.h gl/buffer.cpp gl/buffer.h core/input.cpp core/observer.h util/util.h scene/geometry/plane.cpp scene/geometry/plane.h scene/geometry/sphere.cpp scene/geometry/sphere.h common.h)

add_executable(f2 ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(f2
        glfw
        glm)

set(EXECUTABLE_OUTPUT_PATH ..)
install(TARGETS f2 DESTINATION ${f2_SOURCE_DIR})