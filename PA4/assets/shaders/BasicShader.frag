#version 330 core
out vec4 FragColor;

in vec3 color;

uniform sampler2D texture_diffuse1;

void main(){
	

    FragColor = vec4(color, 1.0);
}