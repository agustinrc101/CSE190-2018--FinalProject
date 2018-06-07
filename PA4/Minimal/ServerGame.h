#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "ServerNetwork.h"
#include "NetworkData.h"
#include "UsefulFunctions.h"

class ServerGame{
public:
	ServerGame(void);
	~ServerGame(void);

	void update();
	void receiveFromClients();
	void sendActionPackets();

private:
	//IDs for the clients connecting for table in ServerNetwork
	static unsigned int client_id;
	//The ServerNetwork object;
	ServerNetwork* network;
	//data buffer
	char network_data[MAX_PACKET_SIZE];
};

