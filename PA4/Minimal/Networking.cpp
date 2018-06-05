#include "Networking.h"

#include "ServerGame.h"
#include "ClientGame.h"
#include <process.h>

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

}

void Networking::serverLoop(void * arg) {
	while (true)
		server->update();
}

void Networking::clientLoop() {
	while (true) {
		//do game stuff
		//call client->update
	}

}