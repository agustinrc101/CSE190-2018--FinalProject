#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <stdio.h>

#include "UsefulFunctions.h"

#define THREE_MAT_SIZE 48

class Networking{
public:
	static void serverLoop(void *);
	void clientLoop(void);

	void update();

	void sendPlayerBodyInfo(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh);

	Networking();
	~Networking();
};

