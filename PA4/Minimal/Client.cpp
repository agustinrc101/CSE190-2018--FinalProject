#include "Client.h"

Client::Client(bool &b) {
	b = connectToServer();
	clientId = 0;
}

bool Client::connectToServer() {
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

	isConnected = true;
	return true;
}

bool Client::connectionErrorHelper() {
	std::cout << "Failed to connect to server ip " << DEFAULT_IP << std::endl;
	return false;
}

Client::~Client() {
	if (isConnected) {
		//Send one last playerInfo message with default values
		char buf[sizeof(Packet)];
		Packet packet;
		packet.type = PLAYER_INFO;
		packet.inSession = false;
		packet.serialize(buf);

		int sendResult = send(sock, buf, sizeof(Packet), 0);

		if (sendResult == SOCKET_ERROR)
			std::cerr << "Error sending packet, Err#" << WSAGetLastError() << std::endl;
	}

	//Close down everything
	closesocket(sock);
	WSACleanup();
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

			switch (packet.type) {
			case UNUSED:
				return;
			case PLAYER_INFO:
				handlePlayerInfo(packet);
				break;
			case OBJECT_INFO:
				handleObjectInfo(packet);
				break;
			default:
				std::cout << "SERVER> Received package of unknown type" << std::endl;
				return;
			}

			i += sizeof(Packet);
		}
	}
}

//Send identity matrices (use for testing)
void Client::sendPacket() {
	char buf[sizeof(Packet)];

	Packet packet;
	packet.type = UNUSED;
	packet.serialize(buf);

	int sendResult = send(sock, buf, sizeof(Packet), 0);
	if (sendResult == SOCKET_ERROR)
		std::cerr << "Error sending packet, Err#" << WSAGetLastError() << std::endl;
}

//Send player data
void Client::sendPacket(glm::mat4 head, glm::mat4 left, glm::mat4 right, int lG, int rG) {
	char buf[sizeof(Packet)];

	Packet packet;
		packet.type = PLAYER_INFO;
		packet.m1 = head;
		packet.m2 = left;
		packet.m3 = right;
		packet.lGrab = lG;
		packet.rGrab = rG;
		packet.inSession = true;
	packet.serialize(buf);

	int sendResult = send(sock, buf, sizeof(Packet), 0);
	if (sendResult == SOCKET_ERROR)
		std::cerr << "Error sending packet, Err#" << WSAGetLastError() << std::endl;
}

//Send object data
void Client::sendPacket(glm::mat4 toWorld, int objId) {
	char buf[sizeof(Packet)];

	Packet packet;
		packet.type = OBJECT_INFO;
		packet.m1 = toWorld;
		packet.objectId = objId;
	packet.serialize(buf);

	int sendResult = send(sock, buf, sizeof(Packet), 0);
	if (sendResult == SOCKET_ERROR)
		std::cerr << "Error sending packet, Err#" << WSAGetLastError() << std::endl;
}

void Client::handlePlayerInfo(Packet & p) {
	hmd = p.m1;
	lh = p.m2;
	rh = p.m3;
	leftGrab = p.lGrab;
	rightGrab = p.rGrab;
	otherConnected = p.inSession;
}

void Client::handleObjectInfo(Packet & p) {
	objChanges.push_back(p);
}

void Client::recievePackets(std::vector<Packet> & v) {
	v = objChanges;
}

void Client::clearVector() {
	objChanges.clear();
}