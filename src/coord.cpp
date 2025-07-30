#include "../include/the_cube/coord.h"


coordinate_sys::coordinate_sys(){

    std::vector<glm::vec3> vertices = {   glm::vec3{-100, 0, 0},
                                glm::vec3{100,0,0},
                                glm::vec3{0, -100, 0},
                                glm::vec3{0, 100, 0},
                                glm::vec3{0, 0, -100},
                                glm::vec3{0, 0, 100}};

    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void coordinate_sys::render(){
    glDrawArrays(GL_LINES, 0, 6);
}

void coordinate_sys::bind_vao(){
    glBindVertexArray(this->vao);
}
