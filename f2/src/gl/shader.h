//
// Created by Dillon Yao on 4/13/18.
//

#ifndef F2_SHADER_H
#define F2_SHADER_H

#include <glad/glad.h>
#include <string>

class Shader {
public:
    ~Shader();
    void load_from_file(const char *filename);
    void compile();

protected:
    GLuint _shader;
    std::string _src;

friend class Program;
};

class VertexShader : public Shader {
public:
    VertexShader();
};

class FragmentShader : public Shader {
public:
    FragmentShader();
};

class Program {
public:
    Program();
    void use();
    void unuse();
    void link();

    void attach_shader(Shader &shader);
    void detach_shader(Shader &shader);
    void detach_all();

    GLint get_uniform_location(const char *name);

    bool is_linked();

private:
    GLuint _program;
};

#endif //F2_SHADER_H
