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

//#define DEFAULT_IP "127.0.0.1"
//#define DEFAULT_IP "192.168.0.128"
//#define DEFAULT_IP "128.54.70.75"
#define DEFAULT_IP "128.54.70.57"
#define DEFAULT_PORT 54000

class Client {
public:
	int clientId;
	bool otherConnected = false;

	Client(bool &b);
	~Client();

	bool connectToServer();

	void sendPacket();
	void sendPacket(glm::mat4 head, glm::mat4 left, glm::mat4 right, int lg, int rg);
	void sendPacket(bool left, bool right);
	void sendPacket(int index);
	void sendPacket(glm::vec3 hitPos);
	void sendPacket(bool connected);

	void update();
	void clearVector();

	//Getters
	glm::mat4 getHmd() { return hmd; }
	glm::mat4 getlh() { return lh; }
	glm::mat4 getrh() { return rh; }
	glm::vec3 getHitPos() { return hitPos; }
	int getLeftGrab() { return leftGrab; }
	int getRightGrab() { return rightGrab; }
	bool getLeftShoot() { return leftShoot; }
	bool getRightShoot() {return rightShoot; }
	std::vector<int> getCanHits() { return canHits; }
	bool getOtherIsConnected() { return otherIsConnected; }

	void resetTriggers() { leftShoot = false; rightShoot = false; }

private:
	SOCKET sock;
	std::vector<int> canHits;
	glm::mat4 hmd = glm::mat4(1.0f);
	glm::mat4 lh = glm::mat4(1.0f);
	glm::mat4 rh = glm::mat4(1.0f);
	glm::vec3 hitPos = glm::vec3(-100.0f);
	int leftGrab = -1;
	int rightGrab = -1;
	bool leftShoot = false;
	bool rightShoot = false;

	bool isConnected = false;
	bool otherIsConnected = false;

	bool connectionErrorHelper();
	void handlePlayerInfo(Packet & p);
	void handleTriggerInfo(Packet & p);
	void handleTargetInfo(Packet & p);
	void handleHitInfo(Packet & p);
	void handleNewPlayer(Packet & p);
};

