//
// Created by Dillon Yao on 4/13/18.
//

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>
#include "shader.h"

Shader::~Shader() {
    glDeleteShader(_shader);
}

void Shader::load_from_file(const char *filename) {
    std::ifstream input(filename);
    if (input.fail()) {
        throw std::runtime_error("Could not open file");
    }
    std::ostringstream output;
    output << input.rdbuf();
    input.close();
    _src = output.str();
}

void Shader::compile() {
    const char *src = _src.c_str();
    glShaderSource(_shader, 1, &src, NULL);
    glCompileShader(_shader);

    GLchar infolog[512];
    GLint success;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        glGetShaderInfoLog(_shader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
        exit(1);
    };
}

VertexShader::VertexShader() {
    _shader = glCreateShader(GL_VERTEX_SHADER);
}

FragmentShader::FragmentShader() {
    _shader = glCreateShader(GL_FRAGMENT_SHADER);
}

Program::Program() {
    _program = glCreateProgram();
};

void Program::use() {
    glUseProgram(_program);
}

void Program::unuse() {
    glUseProgram(0);
}

void Program::link() {
    glLinkProgram(_program);
    GLchar infolog[512];
    GLint success;
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_program, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
        exit(1);
    }
}

void Program::attach_shader(Shader &shader) {
    glAttachShader(_program, shader._shader);
}

void Program::detach_shader(Shader &shader) {
    glDetachShader(_program, shader._shader);
}

void Program::detach_all() {
    GLsizei count;
    GLuint shader[64];

    glGetAttachedShaders(_program, 64, &count, shader);
    for (GLsizei i = 0; i < count; ++i) {
        glDetachShader(_program, shader[i]);
    }
}

GLint Program::get_uniform_location(const char *name) {
    return glGetUniformLocation(_program, name);
}

bool Program::is_linked() {
    GLint success;
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    return success == GL_TRUE;
}
