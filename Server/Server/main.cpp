#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>

#pragma comment (lib, "ws2_32.lib")

#define DEFAULT_PORT 54000
#define MAX_PACKET_SIZE 224

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

	fd_set master;
	FD_ZERO(&master);

	FD_SET(listening, &master);

	int clientNum = 0;

	std::cout << "=====STARTED SERVER=====" << std::endl;

	while (true) {
		fd_set copy = master;
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		for (int i = 0; i < socketCount; i++) {
			SOCKET sock = copy.fd_array[i];
			if (sock == listening) {
				//Accept a new connection
				SOCKET client = accept(listening, nullptr, nullptr);
				//Add the new connection to the list of connected clients
				FD_SET(client, &master);

				//Send a welcome message to the connected clients
				std::string welcomeMsg = "Connected as user number " + std::to_string(clientNum);
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);

				std::cout << "Client connected with message: " << welcomeMsg.c_str() << std::endl;
				clientNum++;
			}
			else {
				//Accept a new message
				char buf[MAX_PACKET_SIZE];
				ZeroMemory(buf, MAX_PACKET_SIZE);

				int bytesIn = recv(sock, buf, MAX_PACKET_SIZE, 0);
				if (bytesIn <= 0) {
					//Drop the client
					std::cout << "Client disconnected" << std::endl;
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else {
					//Send message to other clients, and definetely not the listening socket
					for (int j = 0; j < master.fd_count; j++) {
						SOCKET outSock = master.fd_array[j];
						if (outSock != listening){// && outSock != sock) {							//TODO remove ){//
							
							//std::ostringstream ss;
							//ss << "SOCKET #" << sock << ": " << buf << "\r\n";
							//std::string strOut = ss.str();
							//send(outSock, strOut.c_str(), strOut.size() + 1, 0);
							send(outSock, buf, MAX_PACKET_SIZE, 0);
						}
					}
				}
			}
		}
	}

	//Clean up winsock
	WSACleanup();
	std::cout << "=====CLOSED SERVER=====" << std::endl;
}