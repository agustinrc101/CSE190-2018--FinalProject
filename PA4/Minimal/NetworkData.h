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

struct Packet {							//TOTAL SIZE: 208 bytes
	unsigned int type;					//Size 4 bytes

	int objectId = -1;					//Size 4 bytes
	float lTrigger = -1;				//Size 4 bytes
	float rTrigger = -1;				//Size 4 bytes

	glm::mat4 m1 = glm::mat4(1.0f);		//Size 64 bytes
	glm::mat4 m2 = glm::mat4(1.0f);		//Size 64 bytes
	glm::mat4 m3 = glm::mat4(1.0f);		//Size 64 bytes

	void serialize(char * data) {
		memcpy(data, this, sizeof(Packet));
	}

	void deserialize(char * data) {
		memcpy(this, data, sizeof(Packet));
	}
};

