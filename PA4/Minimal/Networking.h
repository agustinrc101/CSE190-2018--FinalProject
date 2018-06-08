#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <stdio.h>
#include "UsefulFunctions.h"

class Networking{
public:
	bool isConnected = false;

	void update();
	static void clientLoop(void *);
	void sendPlayerBodyInfo(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh);

	Networking();
	~Networking();
};
