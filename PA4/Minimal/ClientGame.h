#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "NetworkData.h"
#include "UsefulFunctions.h"

class ClientGame{
public:
	ClientGame();
	~ClientGame(void);

	ClientNetwork * network;

	char network_data[MAX_PACKET_SIZE];

	void sendActionPackets();
	void sendPlayerInfoPackets(glm::mat4 d1, glm::mat4 d2, glm::mat4 d3);
	void getPlayerInfoPackets();
	void update();
};

