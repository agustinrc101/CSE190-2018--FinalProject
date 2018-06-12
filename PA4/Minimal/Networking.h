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
	bool otherInSession = false;

	void retryConnection();
	static void clientLoop(void *);
	void sendPlayerBodyInfo(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh, int lG, int rG);
	void receivePlayerBodyInfo(glm::mat4 & hmd, glm::mat4 & lh, glm::mat4 & rh, int & lG, int & rG);
	void sendTriggerInfo(bool hand);
	void receiveTriggerInfo(bool & left, bool & right);
	void sendCanHitData(int index);
	void receiveCanHitData(std::vector<int> & v);
	void sendHitInfo(glm::vec3 hitpos);
	void receiveHitInfo(glm::vec3 & hp);
	void clearPacketVector();

	Networking();
	~Networking();
};
