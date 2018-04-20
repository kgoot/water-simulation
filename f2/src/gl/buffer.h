//
// Created by Dillon Yao on 4/14/18.
//

#ifndef F2_BUFFER_H
#define F2_BUFFER_H

#include <glad/glad.h>

class Buffer {
public:
    Buffer();
    ~Buffer();

    void bind();
    void unbind();

    void set_data(unsigned int size, const void *data, GLenum draw_type);

private:
    GLuint _vbo;
};

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void bind();
    void unbind();

    void vertex_attr(unsigned int location, int size, GLenum type, GLboolean normalize, int stride,
                     uint64_t offset);

private:
    GLuint _vao;
};

#endif //F2_BUFFER_H
