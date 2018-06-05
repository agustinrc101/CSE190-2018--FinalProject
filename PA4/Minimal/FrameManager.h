#pragma once

#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <iostream>

//OpenGL
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
//Open AL
#include <al.h>;
#include <alc.h>;
//std
#include <vector>
//our scripts
#include "shader.h"
#include "Skybox.h"



class FrameManager {
public:
	bool setSkyboxPos = true;

	FrameManager();
	~FrameManager();
	void update(double deltaTime);
	
	void drawSkybox(glm::mat4 projection, glm::mat4 view);
	void drawBody(glm::mat4 projection, glm::mat4 view);
	void draw(glm::mat4 projection, glm::mat4 view);

	//Oculus Rift controllers and hmd matrix setters
	void setLeftMat(glm::mat4 m);
	void setRightMat(glm::mat4 m);
	void setHMDMat(glm::mat4 m);

	//ButtonPress
	void pressA();
	void pressB();
	void pressX();
	void pressY();
	void pressLJoystick();
	void pressRJoystick();
	void moveLJoystick(glm::vec2 xy);
	void moveRJoystick(glm::vec2 xy);
	void pressLGrip(float f);
	void pressRGrip(float f);
	void pressLTrigger(float f);
	void pressRTrigger(float f);

private:
	glm::mat4 _leftRift;
	glm::mat4 _rightRift;
	glm::mat4 _hmdRift;

	void init();
	void initShaders();
};

#endif //FRAMEMANAGER_H