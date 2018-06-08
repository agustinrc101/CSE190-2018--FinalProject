#pragma once

#include <string.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#define MAX_PACKET_SIZE 1000000

enum PacketTypes {
	INIT_CONNECTION = 0,
	ACTION_EVENT = 1,
	PLAYER_INFO = 2,
};

struct Packet {
	int clientId;
	glm::mat4 head;
	glm::mat4 leftHand;
	glm::mat4 rightHand;

	void serialize(char * data) {
		memcpy(data, this, sizeof(Packet));
	}

	void deserialize(char * data) {
		memcpy(this, data, sizeof(Packet));
	}
};

