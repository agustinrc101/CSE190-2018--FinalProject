//#include "stdafx.h"
#include "ServerGame.h"

unsigned int ServerGame::client_id;

ServerGame::ServerGame(void){
	//ids to assign clients for our table
	client_id = 0;
	//set up the server network to listen
	network = new ServerNetwork();
}


ServerGame::~ServerGame(){
	delete[] network_data;
	delete(network);
}

void ServerGame::update() {
	//Get new clients
	if (network->acceptNewClient(client_id)) {
		printf("client %d has been connected to the server\n", client_id);
		client_id++;
	}

	receiveFromClients();
}

void ServerGame::receiveFromClients(){
	Packet packet;

	//go through all clients
	std::map<unsigned int, SOCKET>::iterator iter;
	for (iter = network->sessions.begin(); iter != network->sessions.end(); iter++) {
		//Get data for that client
		int data_length = network->receiveData(iter->first, network_data);

		if (data_length <= 0) //no data recieved
			continue;

		unsigned int i = 0;
		while (i < (unsigned int)data_length) {
			packet.deserialize(&(network_data[i]));
			i += sizeof(Packet);

			switch (packet.packet_type) {
			case INIT_CONNECTION:
				printf("Server received init packet from client\n");
				sendActionPackets();
				break;
			case ACTION_EVENT:
				printf("server received action event packet from client\n");
				sendActionPackets();
				break;
			case PLAYER_INFO:
				printf("server received player info from client\n");
				//sendActionPackets();	//????
				break;
			default:
				printf("error in packet type\n");
				break;
			}
		}
	}
}

void ServerGame::sendActionPackets() {
	//send action packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = ACTION_EVENT;

	packet.serialize(packet_data);
	network->sendToAll(packet_data, packet_size);
}
