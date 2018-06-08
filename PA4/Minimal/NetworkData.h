#pragma once

#include <string.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#define MAX_PACKET_SIZE 1000000

enum PacketTypes {
	UNUSED = 0,
	PLAYER_INFO = 1,
	OBJECT_INFO = 2,
	TEST_PACKET = 3,
};

struct Packet {
	int type = PLAYER_INFO;

	//int clientId;
	//glm::mat4 test;

	void serialize(char * data) {
		memcpy(data, this, sizeof(Packet));
	}

	void deserialize(char * data) {
		memcpy(this, data, sizeof(Packet));
	}
};

