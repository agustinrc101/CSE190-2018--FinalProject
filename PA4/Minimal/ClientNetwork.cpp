//#include "stdafx.h"
#include "ClientNetwork.h"

ClientNetwork::ClientNetwork(void) {
	//Create WSADATA obj
	WSADATA wsaData;
	//Socket
	ConnectSocket = INVALID_SOCKET;
	//Holds address info for socket to connect to
	struct addrinfo * result = NULL, 
					*ptr = NULL, 
					hints;
	//Init Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != 0) {
		printf("WSAStrtup failed with error: %d\n", iResult);
		exit(1);
	}

	//Set address info
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;	//TCP connection

	//Resolve server address and port
	iResult = getaddrinfo(DEFAULT_ADDRESS, DEFAULT_PORT, &hints, &result);

	if (iResult != 0) {
		printf("getaddrinfo fauled with error: %d\n", iResult);
		WSACleanup();
		exit(1);
	}

	//Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		//Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			exit(1);
		}

		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			printf("The server is down... did not connect");
		}
	}

	//No longer need address info for server
	freeaddrinfo(result);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		exit(1);
	}

	u_long iMode = 1;
	iResult = ioctlsocket(ConnectSocket, FIONBIO, &iMode);
	if (iResult == SOCKET_ERROR) {
		printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		exit(1);
	}
	//disable nagle (might not need to do this)
	char value = 1;
	setsockopt(ConnectSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
}

ClientNetwork::~ClientNetwork() {
	closesocket(ConnectSocket);
	WSACleanup();
}

int ClientNetwork::receivePackets(char * recvbuf) {
	iResult = NetworkServices::receiveMessage(ConnectSocket, recvbuf, MAX_PACKET_SIZE);
	if (iResult == 0) {
		printf("Connection closed\n");
		closesocket(ConnectSocket);
		WSACleanup();
		exit(1);
	}

	return iResult;
}