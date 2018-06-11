#include "Networking.h"

#include <iostream>
#include <process.h>
#include "Client.h"

Client * client;

Networking::Networking() {
	client = new Client(isConnected);
	if (isConnected)
		_beginthread(clientLoop, 0, (void*)12);
}

Networking::~Networking() {
	delete(client);
}

void Networking::clientLoop(void *) {
	while (true)
		client->update();
}

void Networking::retryConnection() {
	if (!isConnected) {
		isConnected = client->connectToServer();
		if (isConnected)
			_beginthread(clientLoop, 0, (void*)12);
	}
}

void Networking::sendPlayerBodyInfo(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh, int lG, int rG) {
	client->sendPacket(hmd, lh, rh, lG, rG);
}

void Networking::receivePlayerBodyInfo(glm::mat4 & hmd, glm::mat4 & lh, glm::mat4 & rh, int & lG, int & rG) {
	hmd = client->getHmd();
	lh = client->getlh();
	rh = client->getrh();
	lG = client->getLeftGrab();
	rG = client->getRightGrab();
	isConnected = client->otherConnected;
}

void Networking::sendObjectData(glm::mat4 m, int id) {
	client->sendPacket(m, id);
}

void Networking::receiveObjectData(std::vector<Packet> & v) {
	client->recievePackets(v);
}

void Networking::clearPacketVector() {
	client->clearVector();
}
