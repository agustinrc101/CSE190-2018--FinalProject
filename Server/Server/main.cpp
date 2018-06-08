#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

#define DEFAULT_PORT 54000
#define MAX_PACKET_SIZE 1000000

//Source: https://www.youtube.com/watch?v=WDn-htpBlnU
void main() {
	//Initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int ws0k = WSAStartup(ver, &wsData);
	if (ws0k != 0) {
		std::cerr << "Can't initialize winsock! Quitting" << std::endl;
		return;
	}

	//Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		std::cerr << "Can't create a socket... Quitting" << std::endl;
		return;
	}

	//Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(DEFAULT_PORT);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; //Could also use inet_pton ....

	bind(listening, (sockaddr *)&hint, sizeof(hint));

	//Tell Winsock the socket is for listening
	listen(listening, SOMAXCONN);

	//Wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	if (clientSocket == INVALID_SOCKET) {
		std::cerr << "Invalid socket... Quitting" << std::endl;
		return;
	}

	char host[NI_MAXHOST];		//Client's remote name
	char service[NI_MAXHOST];	//Service (i.e. port) the client is connected on

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		std::cout << host << " connected on port " << service << std::endl;
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
	}

	std::cout << service << std::endl;

	//Close listening socket
	closesocket(listening);

	//While loop: accept and echo message back to client
	char buf[MAX_PACKET_SIZE];		//Redo until u can read no bytes

	while (true) {
		ZeroMemory(buf, MAX_PACKET_SIZE);
		//Wait for client to send data
		int bytesReceived = recv(clientSocket, buf, MAX_PACKET_SIZE, 0);
		if (bytesReceived == SOCKET_ERROR) {
			std::cerr << "Error in recv()... Quitting" << std::endl;
			break;
		}

		if (bytesReceived == 0) {
			std::cout << "Client disconnected " << std::endl;
			break;
		}

		//Echo message back to client
		send(clientSocket, buf, bytesReceived + 1, 0);
	}

	//Close socket
	closesocket(clientSocket);

	//Clean up winsock
	WSACleanup();
}