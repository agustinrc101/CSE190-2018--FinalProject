#pragma once

#include <string.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#define MAX_PACKET_SIZE 1000000

enum PacketTypes {
	UNUSED = 0,
	PLAYER_INFO = 1,	//Sends player head and hand matrices and grab status
	TRIGGER_INFO = 2,	//Sends trigger status (if player shot or not)
	TARGET_INFO = 3,	//Sends last object hit (for cans)
	HIT_INFO = 4,		//Sends hit position (to play audio there)
	NEW_PLAYER = 5,
};

struct Packet {							//TOTAL SIZE: 224 bytes
	unsigned int type;					//Size 4 bytes

	int objectId = -1;					//Size 4 bytes
	int lGrab = -1;						//Size 4 bytes
	int rGrab = -1;						//Size 4 bytes

	glm::vec3 hitPos = glm::vec3(-100);	//Size 12 bytes
	glm::mat4 m1 = glm::mat4(1.0f);		//Size 64 bytes
	glm::mat4 m2 = glm::mat4(1.0f);		//Size 64 bytes
	glm::mat4 m3 = glm::mat4(1.0f);		//Size 64 bytes

	bool inSession = false;				//Size 4 bytes
	bool shotLeft = false;				//-----------
	bool shotRight = false;				//-----------
	unsigned int leftWeapon;			//-----------
	unsigned int rightWeapon;			//-----------
										//-----------

	void serialize(char * data) {
		memcpy(data, this, sizeof(Packet));
	}

	void deserialize(char * data) {
		memcpy(this, data, sizeof(Packet));
	}
};

