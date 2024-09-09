#include "../include/glad/glad.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <GLFW/glfw3.h>

#include "../include/the_cube/stb_image.h"
#include "../include/the_cube/shader.h"
#include "../include/the_cube/camera.h"
#include "../include/the_cube/cube.h"
#include "../include/the_cube/constants.h"

void framebuffer_size_callback(GLFWwindow* window, int width =  Screen::width, 
                                                   int height = Screen::height);
void processInput(GLFWwindow *window);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(Screen::width, Screen::height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    Shader ourShader("shaders/shader.vs", "shaders/shader.fs");

    the_cube::Cube cube( // vertices
                    std::array{ glm::vec3(0.5f,  0.5f, 0.0f),
                                 glm::vec3(0.5f, -0.5f, 0.0f),
                                 glm::vec3(-0.5f, -0.5f, 0.0f),
                                 glm::vec3(-0.5f,  0.5f, 0.0f),
                                 glm::vec3(0.5f,  0.5f, 1.0f),
                                 glm::vec3(0.5f, -0.5f, 1.0f),
                                 glm::vec3(-0.5f, -0.5f, 1.0f),
                                 glm::vec3(-0.5f,  0.5f, 1.0f)},
                         // indices 
                                 std::array{0, 1, 3,
                                            1, 2, 3, 
                                                
                                            6, 5, 4,
                                            6, 4, 7,

                                            3, 7, 4,
                                            3, 4, 0,

                                            1, 6, 2,
                                            6, 1, 5,

                                            1, 4, 5,
                                            0, 4, 1,

                                            2, 6, 7,
                                            2, 7, 3});



    Camera c(glm::vec3(2,3,3), 45.f);
    ourShader.use();
    ourShader.setMat4("projection", c.get_projection_matrix());
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();
        ourShader.setMat4("view", c.get_view_matrix());

        cube.bind_vao();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cube.delete_buffers();
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
