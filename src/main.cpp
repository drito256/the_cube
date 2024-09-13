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
void processInput(GLFWwindow *window, the_cube::Cube& cube);

int forward_rotation=0;
int left_rotation=0;
int right_rotation=0;
int backward_rotation=0;

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
    
    Shader shader("shaders/shader.vs", "shaders/shader.fs");

    /*the_cube::Cube cube( // vertices
                    std::array{ glm::vec3(0.5f,  0.5f, -0.5f),
                                 glm::vec3(0.5f, -0.5f, -0.5f),
                                 glm::vec3(-0.5f, -0.5f, -0.5f),
                                 glm::vec3(-0.5f,  0.5f, -0.5f),
                                 glm::vec3(0.5f,  0.5f, 0.5f),
                                 glm::vec3(0.5f, -0.5f, 0.5f),
                                 glm::vec3(-0.5f, -0.5f, 0.5f),
                                 glm::vec3(-0.5f,  0.5f, 0.5f)},
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
*/
    the_cube::Cube cube(glm::vec3(0.f),1);
    Camera c(glm::vec3(-2,3,3), 45.f);
    shader.use();
    shader.setMat4("projection", c.get_projection_matrix());
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //cube.rotate(30,the_cube::RotationDirection::LEFT);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window, cube);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.setMat4("view", c.get_view_matrix());
        shader.setMat4("model", cube.get_model_matrix());

        cube.bind_vao();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cube.delete_buffers();
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window, the_cube::Cube& cube)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        right_rotation++;
        cube.rotate(1, the_cube::RotationDirection::RIGHT);
    }
    else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        left_rotation++;
        cube.rotate(1, the_cube::RotationDirection::LEFT);
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        forward_rotation++;
        cube.rotate(1, the_cube::RotationDirection::FORWARD);
    }
    else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        backward_rotation++;
        cube.rotate(1, the_cube::RotationDirection::BACKWARD);
    }
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
