#include "../include/the_cube/cube.h"

// maybe a good idea to check if non-cube has been passed through vertices
the_cube::Cube::Cube(std::array<glm::vec3, 8> vertices, std::array<int,36> indices){

    // find length of edge regardless of vertices init order
    float max{vertices[0].x}, min{vertices[0].x};
    float x_avg{0}, y_avg{0}, z_avg{0};
    for(int i=0;i<vertices.size();i++){
        max = std::max(max, vertices[i].x);
        min = std::min(min, vertices[i].x);
        
        x_avg += vertices[i].x;
        y_avg += vertices[i].y;
        z_avg += vertices[i].z;
    }
    a = max - min;

    x_avg /= vertices.size();
    y_avg /= vertices.size();
    z_avg /= vertices.size();
    model_matrix = glm::translate(model_matrix,glm::vec3(x_avg, y_avg, z_avg));

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

// TODO: simpler way to construct a cube
the_cube::Cube::Cube(glm::vec3 position, double edge_length){
}

glm::vec3 the_cube::Cube::get_position(){
    return glm::vec3(model_matrix[3][0], model_matrix[3][1], model_matrix[3][2]);
}

glm::mat4 the_cube::Cube::get_model_matrix(){
    return model_matrix;
}

// TODO: fix right and backward rotation
void the_cube::Cube::rotate(int degrees, the_cube::RotationDirection rd){
    float angle = glm::radians(static_cast<float>(degrees));
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);

    // depends on what edge we are rotating it around
    switch(rd){
        case the_cube::RotationDirection::RIGHT:
        trans = glm::translate(trans, -(this->get_position() + glm::vec3(a/2,0,0)));
        rot = glm::rotate(rot, angle, glm::vec3(0,0,1));

        break;
        case the_cube::RotationDirection::LEFT:
        trans = glm::translate(trans, -(this->get_position() - glm::vec3(a/2,0,0)));
        rot = glm::rotate(rot, angle, glm::vec3(0,0,1));
        break;
        case the_cube::RotationDirection::FORWARD:
        trans = glm::translate(trans, -(this->get_position() + glm::vec3(0,0,a/2)));
        rot = glm::rotate(rot, angle, glm::vec3(1,0,0));
        break;
        case the_cube::RotationDirection::BACKWARD:
        trans = glm::translate(trans, -(this->get_position() - glm::vec3(0,0,a/2)));
        rot = glm::rotate(rot, angle, glm::vec3(1,0,0));
        break;
    }
    
    model_matrix = glm::mat4(1.0f);
    model_matrix *= trans;
    model_matrix *= rot;
    model_matrix *= glm::inverse(trans);
}

void the_cube::Cube::bind_vao(){
    glBindVertexArray(vao);
}

void the_cube::Cube::delete_buffers(){
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}
