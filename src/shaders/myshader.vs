#version 330 core
layout (location = 0) in vec3 pos;

uniform vec4 rotate;
out vec4 vertex_color;

void main(){
    gl_Position =  vec4(pos, 1.0f)*vec4(-rotate.x,rotate.y,1.0f,1.0f);
    vertex_color = vec4(1.0f,0.2f,0.5f,1.0f);
    
}
