#version 410 core

uniform int currentIndex = 0;
uniform int chosenIndex = -1;
uniform sampler2D texture0;

in vec3 vertNormal;
in vec2 TexCoords;
out vec4 fragColor;

void main(void) {
    //vec3 color = vertNormal;
    /*if (!all(equal(color, abs(color)))) {
        color = vec3(1.0) - abs(color);
    }*/
	if(currentIndex == chosenIndex)
	{
		fragColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
    else
	{
		//fragColor = vec4(color, 1.0);
		fragColor = texture(texture0, TexCoords);
	}
	//fragColor = vec4(1.0, 1.0, 1.0, 1.0);
}