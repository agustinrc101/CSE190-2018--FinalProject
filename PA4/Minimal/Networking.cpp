#include "Networking.h"

#include <iostream>
#include <process.h>
#include "Client.h"

Client * client;

Networking::Networking() {
	client = new Client(isConnected);
	if (isConnected) {
		_beginthread(clientLoop, 0, (void*)12);
		//TODO send packet that tells server that player connected
	}
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
		if (isConnected) {
			_beginthread(clientLoop, 0, (void*)12);
			//TODO send packet that tells server that player connected
		}
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
	otherInSession = client->otherConnected;
}

void Networking::sendTriggerInfo(bool hand) {
	client->sendPacket(!hand, hand);
}

void Networking::receiveTriggerInfo(bool & left, bool & right) {
	left = client->getLeftShoot();
	right = client->getRightShoot();
}

void Networking::sendCanHitData(int index) {
	client->sendPacket(index);
}

void Networking::receiveCanHitData(std::vector<int> & v) {
	v = client->getCanHits();
}

void Networking::sendHitInfo(glm::vec3 hitPos) {
	client->sendPacket(hitPos);
}

void Networking::receiveHitInfo(glm::vec3 & hp) {
	hp = client->getHitPos();
}

void Networking::clearPacketVector() {
	client->clearVector();
}

bool Networking::checkIfOtherPlayerConnected() {
	return client->getOtherIsConnected();
}
