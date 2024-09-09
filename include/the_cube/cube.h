#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <array>

#include "../glad/glad.h"
#include "../glm/glm.hpp"

namespace the_cube{
    class Cube{
        private:
            std::array<glm::vec3, 8> m_vertices;
            std::array<int, 36> m_indices;
            
            unsigned int vbo = 0; 
            unsigned int vao = 0; 
            unsigned int ebo = 0; 
        // kasnije boja,tekstura ...

        public:
            Cube(std::array<glm::vec3,8> vertices, std::array<int,36> indices);
            void delete_buffers();
            void bind_vao();
            glm::vec3 get_position();
            void rotate(int degrees);
    };
}

#endif
