#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/shader.hpp>
#include <graphics/mesh.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int argc, char const *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Game Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    Shader shader("vert.glsl", "frag.glsl");

    float vertices[] = {
        0.5f,  0.5f, 0.0f,  0.0f, 0.5f, 0.0f,// top right
        0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.5f,// bottom right
        -0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 0.0f,// bottom left
        -0.5f,  0.5f, 0.0f, 0.5f, 0.5f, 0.0f // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    Mesh triangle(vertices, sizeof(vertices) / sizeof(float), indices, sizeof(indices) / sizeof(unsigned int));


    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 2. use our shader program when we want to render an object
        shader.use();
        // 3. now draw the object 
        triangle.draw();
        

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}
