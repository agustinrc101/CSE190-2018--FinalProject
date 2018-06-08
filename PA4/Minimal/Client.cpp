#include "Client.h"



Client::Client() {
	isConnected = connectToServer();
}

bool Client::connectToServer(){
	std::cout << "Connecting to server..." << std::endl;

	std::string ipAddress = DEFAULT_IP;	//IP address of the server
	int port = DEFAULT_PORT;

	//Initialize Winsock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);

	if (wsResult != 0) {
		std::cerr << "Can't start winsock, Err #" << wsResult << std::endl;
		return connectionErrorHelper();
	}
	
	//Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		std::cerr << "Can't create socket, Err#" << WSAGetLastError() << std::endl;
		return connectionErrorHelper();
	}

	//Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
	
	//Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	
	if (connResult == SOCKET_ERROR) {
		std::cerr << "Can't connect to server, Err #" << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return connectionErrorHelper();
	}

	return true;
}

void Client::update() {

}

void Client::sendTestString() {
	//send and receive data
	char buf[MAX_PACKET_SIZE];
	std::string m = "Test string";

	int sendResult = send(sock, m.c_str(), m.size() + 1, 0);
	
	if (sendResult != SOCKET_ERROR) {
		//Wait for response
		ZeroMemory(buf, MAX_PACKET_SIZE);
		int bytesReceived = recv(sock, buf, MAX_PACKET_SIZE, 0);
		if (bytesReceived > 0)
			std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
	}
}

Packet Client::sendPacket(Packet p) {
	Packet pack;
	char data[MAX_PACKET_SIZE];
	p.serialize(data);

	int sendResult = send(sock, data, MAX_PACKET_SIZE + 1, 0);
	if (sendResult != SOCKET_ERROR) {
		char buf[MAX_PACKET_SIZE];
		ZeroMemory(buf, MAX_PACKET_SIZE);
		int bytesReceived = recv(sock, buf, MAX_PACKET_SIZE, 0);
		if (bytesReceived > 0) {
			pack.deserialize(buf);
			std::cout << "SERVER> " << "Received message from client " << pack.clientId << std::endl;
			return pack;
		}
	}

	pack.clientId = -1;
	return pack;
}


Client::~Client(){
	//Close down everything
	closesocket(sock);
	WSACleanup();
}

bool Client::connectionErrorHelper() {
	std::cout << "Failed to connect to server ip " << DEFAULT_IP << std::endl;
	return false;
}
