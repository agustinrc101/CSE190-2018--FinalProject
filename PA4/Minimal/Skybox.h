#ifndef SKYBOX_H
#define SKYBOX_H

#ifdef __APPLE__
// If modern OpenGL replace gl.h with gl3.h
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include<glm/gtc/matrix_transform.hpp>
#include "shader.h"

class Skybox
{
private:
	unsigned int skyboxVAO, skyboxVBO;
	unsigned int cubemapTexture;

	glm::mat4 totalRot;

public:
	Skybox();
	Skybox(std::vector<std::string> faces, Shader* skyboxShaderProgram);
	~Skybox();
	unsigned int loadCubemap(std::vector<std::string> faces);
	void draw(Shader* skyboxShader, const glm::mat4& projection, const glm::mat4& view);

	Skybox& rotate(glm::vec3 rotAxis, float deg);
};

#endif // !SKYBOX_H