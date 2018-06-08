#pragma once

#include <iostream>
#include <WS2tcpip.h>
#pragma comment(lib, "WS2_32.lib")

#include <string>
#include "NetworkData.h"

#define DEFAULT_IP "192.168.0.128"
#define DEFAULT_PORT 54000

class Client{
public:
	bool isConnected = false;

	Client();
	~Client();

	bool  connectToServer();
	void sendTestString();
	Packet sendPacket(Packet p);

	void update();

private:
	SOCKET sock;
	bool connectionErrorHelper();
};

