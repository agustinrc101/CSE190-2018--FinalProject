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
#include "Transform.h"
#include "Geometry.h"
#include "TexturedCube.h"
#include "SoundManager.h"

enum WeaponType {
	HAND = 0,
	GRENADE = 1,
	PISTOL = 2,
	SUBMACHINE = 3,
};

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
	int locomotion(float deltaTime);
	void setUpVector(float x, float y, float z);
	void setFwVector(float x, float y, float z);

private:
	glm::mat4 _leftHand = glm::mat4(1.0f);
	glm::mat4 _rightHand = glm::mat4(1.0f);
	glm::mat4 _head = glm::mat4(1.0f);
	glm::vec3 playerUP = glm::vec3(0, 1, 0);
	glm::vec3 playerFW = glm::vec3(0, 0, -1);
	
	bool pressedLeftGrip = false;
	bool pressedRightGrip = false;

	void initSkybox();
	void initShaders();
	void initObjects();
	void initSoundManager();

	void updateTime(double dT);

	void getNetworkData();
	void setOtherPlayerInfo(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh);

	void moveGrabbedObj();
	void checkProximity();

	void setUpLocomotionData();
	void locomotionHelper(float higher, float lower);
};

#endif //FRAMEMANAGER_H