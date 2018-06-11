#pragma once

#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <iostream>

//OpenGL
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
//Open AL
#include <al.h>
#include <alc.h>
//std
#include <vector>
//our scripts
#include "shader.h"
#include "Skybox.h"
#include "Networking.h"
#include "NetworkData.h"
#include "Scene.h"
#include "TexturedCube.h"
#include "SoundManager.h"

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
	void setPlayer(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh);
	void setPlayerHandPosition(glm::mat4 lh, glm::mat4 rh);

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
	bool locomotion(float deltaTime);

private:
	glm::mat4 _leftHand = glm::mat4(1.0f);
	glm::mat4 _rightHand = glm::mat4(1.0f);
	glm::mat4 _head = glm::mat4(1.0f);
	
	bool pressedLeftGrip = false;
	bool pressedRightGrip = false;
	
	float _leftTrigger;
	float _rightTrigger;

	void initSkybox();
	void initShaders();
	void initObjects();
	void initSoundManager();

	void getNetworkData();
	void setOtherPlayerInfo(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh, float lT, float rT);

	void setUpLocomotionData();
	void locomotionHelper(float higher, float lower);
};

#endif //FRAMEMANAGER_H