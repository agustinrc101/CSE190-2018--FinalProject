#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <winsock2.h>
#include <Windows.h>
#include "NetworkServices.h"
#include <ws2tcpip.h>
#include <stdio.h>
#include "NetworkData.h"

//Buffer size
#define DEFAULT_BUFLEN 512
//Port to connect sockets through
#define DEFAULT_PORT "6881"
//address to connect to
#define DEFAULT_ADDRESS "128.54.70.75"
#define LOCAL_HOST "127.0.0.1"
//Need to link with ws2_32.lib, mswsock.lib, and advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class ClientNetwork{
public:
	//For error checking functions calls in winsock library
	int iResult;
	//Socket for client to connect to server
	SOCKET ConnectSocket;
	//ctor/dtor
	ClientNetwork(void);
	~ClientNetwork(void);

	int receivePackets(char *);
};