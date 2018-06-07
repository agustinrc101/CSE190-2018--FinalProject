#pragma once

#include <string.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#define MAX_PACKET_SIZE 1000000

enum PacketTypes {
	INIT_CONNECTION = 0,
	ACTION_EVENT = 1,
	PLAYER_INFO = 2,		//hmd, lhand, rhand, trigger
};

struct Packet {
	unsigned int packet_type;
	//float data[16];
	glm::mat4 body[3];


	void serialize(char * data) {
		memcpy(data, this, sizeof(Packet));
	}

	void deserialize(char * data) {
		memcpy(this, data, sizeof(Packet));
	}
};

