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

}

void ServerGame::update() {
	//Get new clients
	if (network->acceptNewClient(client_id)) {
		printf("client %d has been connected to the server\n", client_id);
		client_id++;
	}
}
