#include "../include/the_cube/tile.h"


the_cube::Tile::Tile(std::array<glm::vec3, 6> vertices){

      m_vertices = vertices;
      glGenVertexArrays(1, &vao);
      glGenBuffers(1, &vbo);
 
      glBindVertexArray(vao);
 
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW);
 
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
      glEnableVertexAttribArray(0);

      color = glm::vec3(1,1,1);
}

void the_cube::Tile::render(){
    bind_vao();
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
}

glm::vec3 the_cube::Tile::get_color(){
    return color;
}

void the_cube::Tile::bind_vao(){
    glBindVertexArray(vao);
}

