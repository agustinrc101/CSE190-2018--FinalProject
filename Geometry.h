#ifndef GEOMETRY_H
#define GEOMETRY_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#include<GLFW/glfw3.h>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<iostream>
#include<stdio.h>
#include<vector>
#include<string>
#include<algorithm>
#include<stack>
#include"Node.h"
#include"shader.h"
#include"model.h"

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

class Geometry : public Node
{
public:
	Geometry();
	~Geometry();
	Geometry& init(std::string filepath = "", std::string ppmpath = "");
	void update();
	int draw(glm::mat4 C, Shader* shaderProgram, int n = 0);
	void addTexture(std::string file);
	std::vector<glm::vec3>& getVertices();
	std::vector<glm::vec3>& getNormals();
	std::vector<unsigned int>& getIndices();
	void centerForTerrain();
	glm::mat4 getToWorld(glm::mat4 C = glm::mat4(1.0f)) final;

protected:

private:
	bool initialized;
	Model model;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> tindices;
	std::vector<unsigned int> nindices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoord;
	glm::mat4 toWorld;
	glm::mat4 totalRot;
	glm::mat4 rotOffset;
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	GLuint TBO;
	GLuint NBO;
	GLuint textureID;
	float scalePointAmount;
	float scaleAmount;
	float baseX;
	float baseY;
	float baseZ;
	float x;
	float y;
	float z;
	bool transFirst;
	bool hasTexture;

	void parse(const char* filepath);
	void centerAndResize();
};

#endif
