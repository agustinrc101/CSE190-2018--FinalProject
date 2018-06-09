#include "Client.h"

Client::Client(bool &b) {
	b = connectToServer();
	clientId = 0;
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
	std::cout << "Connection successful!" << std::endl;
	
	{
		//Get welcome message
		char buffer[MAX_PACKET_SIZE];
		ZeroMemory(buffer, MAX_PACKET_SIZE);
		int bytesReceived = recv(sock, buffer, MAX_PACKET_SIZE, 0);
		if (bytesReceived > 0)
			std::cout << "SERVER> " << std::string(buffer, 0, bytesReceived) << std::endl;
	}

	return true;
}

void Client::update() {	//Runs in a separate thread
	char data[MAX_PACKET_SIZE];
	ZeroMemory(data, MAX_PACKET_SIZE);
	Packet packet;

	int bytesReceived = recv(sock, data, sizeof(Packet), 0);

	int i = 0;
	if (bytesReceived > 0) {
		while (i < bytesReceived) {
			packet.deserialize(&(data[i]));

			switch(packet.type) {
			case UNUSED:
				std::cout << "SERVER> Received package of type UNUSED" << std::endl;
				return;
			case PLAYER_INFO:
				std::cout << "SERVER> Received package of type PLAYER_INFO" << std::endl;
				UsefulFunctions::printMatrix(packet.m1);

				break;
			case OBJECT_INFO:
				std::cout << "SERVER> Received package of type OBJECT_INFO" << std::endl;
				break;
			default:
				std::cout << "SERVER> Received package of unknown type" << std::endl;
				return;
			}

			i += sizeof(Packet);
		}
	}
}

void Client::sendTestString() {
	//send and receive data
	char buf[MAX_PACKET_SIZE];
	std::string m = "Test string";

	int sendResult = send(sock, m.c_str(), m.size() + 1, 0);
	
	if (sendResult == SOCKET_ERROR)
		std::cerr << "Error sending test string" << std::endl;
}

void Client::sendPacket() {
	char buf[sizeof(Packet)];

	Packet packet;
	packet.type = OBJECT_INFO;
	packet.m1 = glm::mat4(1.0f);
	packet.m2 = glm::mat4(1.0f);
	packet.m3 = glm::mat4(1.0f);
	//packet.clientId = 0;
	//packet.test = glm::mat4(1.0f);
	packet.serialize(buf);

	int sendResult = send(sock, buf, sizeof(Packet), 0);
	if (sendResult == SOCKET_ERROR)
		std::cerr << "Error sending packet, Err#" << WSAGetLastError() << std::endl;
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
