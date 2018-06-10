#pragma once

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include "UsefulFunctions.h"

//Open AL
#include <al.h>
#include <alc.h>

//irrKlang
//#include <irrKlang.h>

class SoundManager {
public:
	SoundManager();
	~SoundManager();
	void playSound();
	void loadSound(std::string file);
	void testing(std::string file);

private:
	ALCdevice* device;
	ALCcontext *context;

	void init();
	static inline ALenum to_al_format(short channels, short samples);
	
};

#endif //SOUNDMANAGER_H