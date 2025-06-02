#include <graphics/shader.hpp>

char* read_shader_source(std::string file_name) {
    std::ostringstream oss;
    oss << RESOURCES << "/shaders/" << file_name;
    
    std::ifstream vertexShaderSourceStream(oss.str(), std::ios::in | std::ios::binary);

    if (!vertexShaderSourceStream.is_open()) {
        std::cerr << "Error opening the shader source!" << std::endl;
    }

    vertexShaderSourceStream.seekg(0, std::ios::end);
    std::streamsize fileSize = vertexShaderSourceStream.tellg();  // Get file size
    vertexShaderSourceStream.seekg(0, std::ios::beg);

    // Allocate memory for the file content
    char* buffer = new char[fileSize + 1];  // +1 for null terminator (if needed)

    // Read the content of the file into the buffer
    if (vertexShaderSourceStream.read(buffer, fileSize)) {
        // Add a null terminator (in case the file is treated as a C-style string)
        buffer[fileSize] = '\0';
    }

    return buffer;
}

unsigned int create_shader(char* source, GLenum flag) {
    if (flag == GL_VERTEX_SHADER || flag == GL_FRAGMENT_SHADER) {
        unsigned int shader;
        shader = glCreateShader(flag);

        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        int  success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << flag << "::COMPILATION_FAILED\n" << infoLog << std::endl;
            return -1;
        }

        return shader;
    } else {
        std::cerr << "Wrong shader type specified" << std::endl;
        return -1;
    }  
}

Shader::Shader(std::string vertexShaderFile, std::string fragmentShaderFile)
{
    char *vertexShaderSource = read_shader_source(vertexShaderFile);
    char *fragmentShaderSource = read_shader_source(fragmentShaderFile);

    unsigned int vertexShader = create_shader(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = create_shader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    int  success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << "PROGRAM" << "::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(ID);
}