#include "../include/the_cube/cube.h"



the_cube::Cube::Cube(std::array<glm::vec3, 8> vertices, std::array<int,36> indices){
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
}



glm::vec3 the_cube::Cube::get_position(){
    float x_avg{}, y_avg{}, z_avg{};

    for(int i=0;i<8;i++){
        x_avg += m_vertices[i].x;
        y_avg += m_vertices[i].y;
        z_avg += m_vertices[i].z;
    }

    x_avg /= 8;
    y_avg /= 8;
    z_avg /= 8;

    return glm::vec3(x_avg, y_avg, z_avg);
}

void the_cube::Cube::rotate(int degrees){

}

void the_cube::Cube::bind_vao(){
    glBindVertexArray(vao);
}

void the_cube::Cube::delete_buffers(){
    if (vao != 0 && glIsVertexArray(vao)) {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }

    if (vbo != 0 && glIsBuffer(vbo)) {
        glDeleteBuffers(1, &vbo);
        vbo = 0;
    }

    if (ebo != 0 && glIsBuffer(ebo)) {
        glDeleteBuffers(1, &ebo);
        ebo = 0;
    }
}
