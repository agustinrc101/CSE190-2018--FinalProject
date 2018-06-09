#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <stdio.h>
#include <vector>
#include "UsefulFunctions.h"
#include "NetworkData.h"

class Networking {
public:
	bool isConnected = false;

	void retryConnection();
	static void clientLoop(void *);
	void sendPlayerBodyInfo(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh, float lT, float rT);
	void receivePlayerBodyInfo(glm::mat4 & hmd, glm::mat4 & lh, glm::mat4 & rh, float & lT, float & rT);
	void receiveObjectData(std::vector<Packet> & v);
	void clearPacketVector();

	Networking();
	~Networking();
};
