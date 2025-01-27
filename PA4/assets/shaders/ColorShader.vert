#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 rgb;

void main(){
    color = rgb;    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}