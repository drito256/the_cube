#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <array>


#include "../glm/glm.hpp"

class Cube{
    private:
        std::array<glm::vec3, 8> m_vertices;
        std::array<int, 36> m_indices;

        // vbo, vao, ebo
    
    // kasnije boja,tekstura ...

    public:
        Cube(std::array<glm::vec3,8> vertices, std::array<int,36> indices)
            :m_vertices{vertices}
            ,m_indices{indices}
            {}
        void rotate(int degrees);
};

#endif
