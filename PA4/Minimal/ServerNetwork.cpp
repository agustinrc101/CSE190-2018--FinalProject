//#include "stdafx.h"
#include "ServerNetwork.h"

ServerNetwork::ServerNetwork(void){
	//Create WSADATA object
	WSAData wsaData;
	//Our sockets for the user
	ListenSocket = INVALID_SOCKET;
	ClientSocket = INVALID_SOCKET;
	//Address info for the server to listen to
	struct addrinfo * result = NULL;
	struct addrinfo hints;
	//Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		exit(1);
	}

	//Set address information
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP; //TCP Connection
	hints.ai_flags = AI_PASSIVE;
	
	//Server doesn't need an address because it'll be in the local machine
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		exit(1);
	}

	//Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		exit(1);
	}

	//Set the mode of the socket to be nonblocking
	u_long iMode = 1;
	iResult = ioctlsocket(ListenSocket, FIONBIO, &iMode);
	if (iResult == SOCKET_ERROR) {
		printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}

	//Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bid failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}

	//No longer need address info
	freeaddrinfo(result);
	//Start listening for new lcinets attempting to connect
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}

}


ServerNetwork::~ServerNetwork(void){

}

bool ServerNetwork::acceptNewClient(unsigned int & id) {
	//if client waiting, accept the connection and save the socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket != INVALID_SOCKET) {
		//Disable nagle on client's socket (might not have to do this)
		char value = 1;
		setsockopt(ClientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
		//Insert new client into session id table
		sessions.insert(pair<unsigned int, SOCKET>(id, ClientSocket));
		
		return true;
	}

	return false;
}
