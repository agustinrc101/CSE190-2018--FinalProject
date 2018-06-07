//#include "stdafx.h"
#include "ClientGame.h"


ClientGame::ClientGame(void){
	network = new ClientNetwork();

	//send init packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = INIT_CONNECTION;

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

ClientGame::~ClientGame(){
	delete[] network_data;
	delete(network);
}

void ClientGame::sendActionPackets() {
	//send action packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = ACTION_EVENT;

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientGame::sendPlayerInfoPackets(glm::mat4 d1, glm::mat4 d2, glm::mat4 d3) {
	//send player info packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = PLAYER_INFO;
	
	/*
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			packet.data[j + (i * 4)] = float(d1[j][i]);
	*/

	packet.body[0] = d1;
	packet.body[1] = d2;
	packet.body[2] = d3;

	packet.serialize(packet_data);
	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientGame::update() {
	Packet packet;
	int data_length = network->receivePackets(network_data);

	if (data_length <= 0) //No data recieved
		return;

	unsigned int i = 0;
	while (i < (unsigned int)data_length) {
		packet.deserialize(&(network_data[i]));
		i += sizeof(Packet);

		switch (packet.packet_type) {
		case ACTION_EVENT:
			//printf("client recieved action event packet form server\n");
			sendActionPackets();
			break;
		case PLAYER_INFO:
			printf("client received player info packet from server\n");
			//UsefulFunctions::printMatrix(packet.body[0]);
			getPlayerInfoPackets();
			break;
		default:
			printf("error in packet types\n");
			break;
		}
	}
}

void ClientGame::getPlayerInfoPackets() {
	
}