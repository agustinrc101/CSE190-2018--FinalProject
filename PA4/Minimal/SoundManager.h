#pragma once

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include <unordered_map>
#include "UsefulFunctions.h"

//Open AL
#include <al.h>
#include <alc.h>

#include "SoundBox.h"
#include "SoundEar.h"

class SoundEar;
class SoundBox;

class SoundManager {
public:
	SoundManager();
	~SoundManager();
	void playSound(ALuint source, ALfloat* sourcePos, ALint buffer);
	ALuint loadSound(std::string file);
	SoundBox* createSource();
	SoundEar* createListener();
	void testing(std::string file);
	void testing2(ALuint source, ALfloat* sourcePos, ALint buffer1, std::string file);

private:
#define BYTE (sizeof(char))
#define TWOBYTE (sizeof(char)*2)
#define FOURBYTE (sizeof(char)*4)

	ALCdevice* device;
	ALCcontext* context;
	std::vector<SoundBox*> sources;
	std::vector<ALuint> buffers;
	std::vector<SoundEar*> listeners;
	std::vector<char*> soundBuffers;

	void init();
	static inline ALenum to_al_format(short channels, short samples);
	
};

#endif //SOUNDMANAGER_H