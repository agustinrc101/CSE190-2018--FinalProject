#include "Networking.h"

#include <process.h>
#include "ServerGame.h"
#include "ClientGame.h"
#include <iostream>

ServerGame * server;
ClientGame * client;

Networking::Networking() {
	//Initialize the server
	server = new ServerGame();
	//Create thread with arbitrary argument for the run function
	_beginthread(serverLoop, 0, (void*)12);
	//Initialize the client
	client = new ClientGame();

	clientLoop();
}

Networking::~Networking(){
	delete(server);
	delete(client);
}

void Networking::update() {
	clientLoop();
	//std::cout << sizeof(Packet) << std::endl;
}

void Networking::serverLoop(void * arg) {
	while (true)
		server->update();
}

void Networking::clientLoop() {
	client->update();
}

void Networking::sendPlayerBodyInfo(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh) {
	float data[16];

	int index = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			data[index] = hmd[i][j];
	}

	client->sendPlayerInfoPackets(data);
}