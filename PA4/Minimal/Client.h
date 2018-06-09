#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include <WS2tcpip.h>
#pragma comment(lib, "WS2_32.lib")

#include <string>
#include <vector>

#include "NetworkData.h"
#include "UsefulFunctions.h"

//#define DEFAULT_IP "192.168.0.128"
#define DEFAULT_IP "128.54.70.75"
#define DEFAULT_PORT 54000

class Client {
public:
	int clientId;

	Client(bool &b);
	~Client();

	bool connectToServer();

	void sendPacket();
	void sendPacket(glm::mat4 head, glm::mat4 left, glm::mat4 right, float lT, float rT);
	void sendPacket(glm::mat4 toWorld, int objId);

	void update();

	void clearVector();

	//Getters
	void recievePackets(std::vector<Packet> & v);
	glm::mat4 getHmd() { return hmd; }
	glm::mat4 getlh() { return lh; }
	glm::mat4 getrh() { return rh; }
	float getlTrigger() { return lTriggerStatus; }
	float getrTrigger() { return rTriggerStatus; }

private:
	SOCKET sock;
	std::vector<Packet> objChanges;
	glm::mat4 hmd = glm::mat4(1.0f);
	glm::mat4 lh = glm::mat4(1.0f);
	glm::mat4 rh = glm::mat4(1.0f);
	float lTriggerStatus = -1;
	float rTriggerStatus = -1;

	bool isConnected = false;

	bool connectionErrorHelper();
	void handlePlayerInfo(Packet & p);
	void handleObjectInfo(Packet & p);
};

