#version 330 core

uniform int currentIndex = 0;
uniform int chosenIndex = -1;
uniform sampler2D texture0;

in vec3 vertNormal;
in vec2 TexCoords;
out vec4 fragColor;

void main() {
    //vec3 color = vertNormal;
	if(currentIndex == chosenIndex){
		fragColor = vec4(1.0, 0.0, 1.0, 1.0);
	}
    else{
		fragColor = texture(texture0, TexCoords);
	}
}