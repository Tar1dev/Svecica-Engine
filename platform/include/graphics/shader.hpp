#if !defined(SHADER_HPP)
#define SHADER_HPP

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

char* read_shader_source(std::string file_name);
unsigned int create_shader(char* source, GLenum flag);

class Shader
{
private:
    unsigned int ID;
public:
    Shader(std::string, std::string);
    void use();
};


#endif // SHADER_HPP
