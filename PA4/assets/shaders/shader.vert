#version 410 core

uniform mat4 projection = mat4(1);
uniform mat4 view = mat4(1);
uniform mat4 model = mat4(1);

layout(location = 0) in vec4 Position;
layout(location = 1) in vec3 Normal;
layout (location = 2) in vec2 aTexCoords;

out vec3 vertNormal;
out vec2 TexCoords;

void main(void) {
   vertNormal = Normal;
   TexCoords = aTexCoords;
   gl_Position = projection * view * model * Position;
}
