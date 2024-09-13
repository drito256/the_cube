#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <array>

#include "../glad/glad.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "constants.h"

namespace the_cube{

    enum class RotationDirection{
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    class Cube{
        private:
            std::array<glm::vec3, 8> m_vertices;
            std::array<int, 36> m_indices;

            float a{0}; // edge length
            glm::mat4 model_matrix{glm::mat4(1.f)}; // identity
            
            unsigned int vbo; 
            unsigned int vao; 
            unsigned int ebo; 

            // kasnije boja,tekstura ...

        public:
            Cube(std::array<glm::vec3,8> vertices, std::array<int,36> indices);
            Cube(glm::vec3 position, float edge_length);

            void delete_buffers();
            void bind_vao();
            void rotate(int degrees, RotationDirection rd);
            void reset_position();

            glm::vec3 get_position();
            glm::mat4 get_model_matrix();
    };
}

#endif
