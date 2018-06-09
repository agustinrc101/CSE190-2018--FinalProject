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
};

struct Packet {	//Size 196
	unsigned int type;	//Size 4

	glm::mat4 m1;		//Size 64
	glm::mat4 m2;		//Size 64
	glm::mat4 m3;		//Size 64

	void serialize(char * data) {
		memcpy(data, this, sizeof(Packet));
	}

	void deserialize(char * data) {
		memcpy(this, data, sizeof(Packet));
	}
};

