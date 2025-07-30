#ifndef COORD_H
#define COORD_H

#include "../glad/glad.h"
#include "../glm/glm.hpp"

#include <vector>

class coordinate_sys{
public:
    coordinate_sys();


    void bind_vao();
    void render();

private:
    unsigned int vao, vbo;

};



#endif
