#pragma once

#ifndef SOUNDEAR_H
#define SOUNDEAR_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include "UsefulFunctions.h"

//Open AL
#include <al.h>
#include <alc.h>

#include "SoundManager.h"

class SoundManager;

class SoundEar {
public:
	SoundEar() {}
	SoundEar(ALuint source, SoundManager* soundManager);
	~SoundEar();
	void setPos(glm::vec3 pos);
	void setPos(float x, float y, float z);
	void setOrien(glm::mat4 orien);
	glm::mat4 getOrien();
	ALuint getID();
	glm::vec3 getPos();

private:
	ALuint listener;
	SoundManager* soundManager;
	glm::vec3 pos;
	glm::mat4 orien;

};

#endif //SOUNDEAR_H