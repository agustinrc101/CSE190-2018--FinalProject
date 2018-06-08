#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include <WS2tcpip.h>
#pragma comment(lib, "WS2_32.lib")

#include <string>
#include "NetworkData.h"
#include "UsefulFunctions.h"

#define DEFAULT_IP "192.168.0.128"
#define DEFAULT_PORT 54000

class Client{
public:
	int clientId;

	Client(bool &b);
	~Client();

	bool  connectToServer();
	void sendTestString();
	void sendPacket();

	void update();

private:
	SOCKET sock;
	bool connectionErrorHelper();
};

