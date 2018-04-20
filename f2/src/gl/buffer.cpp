//
// Created by Dillon Yao on 4/14/18.
//

#include "buffer.h"

Buffer::Buffer() {
    glGenBuffers(1, &_vbo);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &_vbo);
}

void Buffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
}

void Buffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::set_data(unsigned int size, const void *data, GLenum usage) {
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &_vao);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &_vao);
}

void VertexArray::bind() {
    glBindVertexArray(_vao);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

void VertexArray::vertex_attr(unsigned int location, int size, GLenum type, GLboolean normalize, int stride,
                              uint64_t offset) {
    glVertexAttribPointer(location, size, type, normalize, stride, (void *) offset);
    glEnableVertexAttribArray(location);
}
