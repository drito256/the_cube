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
// position is center of the cube
the_cube::Cube::Cube(glm::vec3 position, double edge_length){
    a = edge_length;
    model_matrix = glm::translate(model_matrix, position);

    // lower 4 vertices
    m_vertices[0] = position - glm::vec3(edge_length/2);
    m_vertices[1] = position - glm::vec3(edge_length/2, edge_length/2, -edge_length/2);
    m_vertices[2] = position - glm::vec3(-edge_length/2, edge_length/2, -edge_length/2);
    m_vertices[3] = position - glm::vec3(-edge_length/2, edge_length/2, edge_length/2);

    // upper 4
    m_vertices[4] = position + glm::vec3(edge_length/2);
    m_vertices[5] = position + glm::vec3(edge_length/2, edge_length/2, -edge_length/2);
    m_vertices[6] = position + glm::vec3(-edge_length/2, edge_length/2, -edge_length/2);
    m_vertices[7] = position + glm::vec3(-edge_length/2, edge_length/2, edge_length/2);

    // order is important because of face culling
    m_indices = {
        1,2,4,
        1,4,7,

        2,3,5,
        2,5,4,

        3,6,5,
        3,0,6,

        7,6,0,
        7,0,1,

        6,7,4,
        6,4,5,

        2,1,0,
        3,2,0
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
}

glm::vec3 the_cube::Cube::get_position(){
    return glm::vec3(model_matrix[3][0], model_matrix[3][1], model_matrix[3][2]);
}

void the_cube::Cube::reset_position(){
    model_matrix[3][0] = 0.f;
    model_matrix[3][1] = 0.f;
    model_matrix[3][2] = 0.f;
}

glm::mat4 the_cube::Cube::get_model_matrix(){
    return model_matrix;
}

// TODO: fix right and backward rotation
void the_cube::Cube::rotate(int degrees, the_cube::RotationDirection rd){
    float angle = glm::radians(static_cast<float>(degrees));

    glm::mat4 rotation_translation = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);

    // depends on what edge we are rotating it around
    switch(rd){
        case the_cube::RotationDirection::RIGHT:
        rotation_translation = glm::translate(rotation_translation, glm::vec3(0
                                                               ,static_cast<float>(a)/2
                                                               ,-static_cast<float>(a)/2));
        rot = glm::rotate(rot, angle, glm::vec3(1,0,0));
        break;
        case the_cube::RotationDirection::LEFT:
        rotation_translation = glm::translate(rotation_translation, glm::vec3(0
                                                               ,static_cast<float>(a)/2,
                                                               static_cast<float>(a)/2));
        rot = glm::rotate(rot, angle, glm::vec3(1,0,0));
        break;
        case the_cube::RotationDirection::FORWARD:
        rotation_translation = glm::translate(rotation_translation, glm::vec3(-static_cast<float>(a)/2
                                                               ,static_cast<float>(a)/2,0));
        rot = glm::rotate(rot, angle, glm::vec3(0,0,1));
        break;
        case the_cube::RotationDirection::BACKWARD:
        rotation_translation = glm::translate(rotation_translation,  glm::vec3(static_cast<float>(a)/2
                                                               ,static_cast<float>(a)/2,0));
        rot = glm::rotate(rot, angle, glm::vec3(0,0,1));
        break;
    }
    glm::vec3 world_translation = get_position();
    reset_position();

    // translacija za rotaciju oko odredene osi
    model_matrix *= rotation_translation;
    model_matrix *= rot;
//    model_matrix *= glm::inverse(rotation_translation);

//    model_matrix = glm::translate(model_matrix, world_translation);
}

void the_cube::Cube::bind_vao(){
    glBindVertexArray(vao);
}

void the_cube::Cube::delete_buffers(){
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}
