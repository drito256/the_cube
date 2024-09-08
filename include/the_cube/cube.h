#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <array>


#include "../glm/glm.hpp"

namespace the_cube{
    class Cube{
        private:
            std::array<glm::vec3, 8> m_vertices;
            std::array<int, 36> m_indices;
            
            unsigned int vbo; 
            unsigned int vao; 
            unsigned int ebo; 
        // kasnije boja,tekstura ...

        public:
            Cube(std::array<glm::vec3,8> vertices, std::array<int,36> indices);
            void rotate(int degrees);
    };
}

#endif
