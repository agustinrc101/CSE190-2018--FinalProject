#pragma once

#ifndef SOUNDBOX_H
#define SOUNDBOX_H

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

class SoundBox {
public:
	SoundBox() {}
	//SoundBox(ALuint source, SoundManager* soundManager);
	SoundBox(SoundManager* soundManager);
	~SoundBox();
	void playSound(unsigned int sound, float volume = 1.0f);
	void playSound(std::string sound);
	unsigned int loadSound(std::string file);
	void setPos(glm::vec3 pos);
	void setPos(float x, float y, float z);
	ALuint getID();

private:
    ALuint source;
	SoundManager* soundManager;
	glm::vec3 pos;

};

#endif //SOUNDBOX_H