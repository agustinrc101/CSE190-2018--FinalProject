#include "Networking.h"

#include <iostream>
#include "Client.h"
#include "NetworkData.h"

Client * client;

Networking::Networking() {
	client = new Client();
}

Networking::~Networking(){
	delete(client);
}

void Networking::update() {
	if (client->isConnected) {
		//TODO
	}
	else
		client->isConnected = client->connectToServer();
}

void Networking::sendPlayerBodyInfo(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh) {
	if (client->isConnected) {
		Packet packet;
		packet.clientId = 0;
		packet.head = hmd;
		packet.leftHand = lh;
		packet.rightHand = rh;

		Packet test = client->sendPacket(packet);

		UsefulFunctions::printMatrix(test.head);
	}
	else
		client->isConnected = client->connectToServer();
}

void Networking::sendMessage() {
	if (client->isConnected)
		client->sendTestString();
	else
		client->isConnected = client->connectToServer();
}

