#include "Networking.h"

#include <iostream>
#include <process.h>
#include "Client.h"
#include "NetworkData.h"

Client * client;

Networking::Networking() {
	client = new Client(isConnected);
	_beginthread(clientLoop, 0, (void*)12);
}

Networking::~Networking(){
	delete(client);
}

void Networking::update() {
	if (isConnected) {}
	else
		isConnected = client->connectToServer();
}

void Networking::clientLoop(void *) {
	while (true)
		client->update();
}

void Networking::sendPlayerBodyInfo(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh) {
	if (isConnected)
		client->sendPacket();
	else 
		isConnected = client->connectToServer();
}

