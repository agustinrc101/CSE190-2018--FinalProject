#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 pos;

uniform sampler2D texture_diffuse1;
uniform vec3 eye;

void main(){
	float o = 1.0;
	vec4 base = texture(texture_diffuse1, TexCoords);
	FragColor = vec4(o * base.x, o * base.y, o * base.z, 1.0);
}