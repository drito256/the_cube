#ifndef TILE_H
#define TILE_H

#include <array>

#include "../glad/glad.h"
#include "../glm/glm.hpp"

namespace the_cube{
    class Tile{
        private:
            std::array<glm::vec3, 6> m_vertices;

            unsigned int vao;
            unsigned int vbo;

            glm::vec3 color;

            void bind_vao();


        public:
            Tile(std::array<glm::vec3, 6> vertices);

            void render();
            glm::vec3 get_color();
    };
}


#endif
