#pragma once

#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "ShaderLoader.h"
#include "Skybox.h"

class FrameManager {
public:
	bool setSkyboxPos = true;

	FrameManager();
	~FrameManager();
	void update(double deltaTime);
	
	void drawSkybox(glm::mat4 projection, glm::mat4 headPose);
	void drawControllers(glm::mat4 projection, glm::mat4 headPose);
	void draw(glm::mat4 projection, glm::mat4 headPose);

	void setControllerPositions(glm::vec3 l, glm::vec3 r);

	//Application Specific
	void setHMDPos(glm::vec3 pos);

	//ButtonPress
	void pressA();
	void pressB();
	void pressX();
	void pressY();

private:
	void init();
	void initShaders();
};

#endif //FRAMEMANAGER_H