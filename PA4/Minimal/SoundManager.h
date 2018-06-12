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

#include <SFML\Audio.hpp>

class SoundEar;
class SoundBox;

class SoundManager {
public:
	SoundManager();
	~SoundManager();
	//void playSound(ALuint source, ALfloat* sourcePos, ALint buffer);
	void playSound(glm::vec3 sourcePos, unsigned int buffer, float volume);
	ALuint loadSound(std::string file);
	SoundBox* createSource();
	SoundEar* createListener();
	void testing(std::string file);
	void testing2(ALuint source, ALfloat* sourcePos, ALint buffer1, std::string file);
	void update();

private:
#define BYTE (sizeof(char))
#define TWOBYTE (sizeof(char)*2)
#define FOURBYTE (sizeof(char)*4)

	ALCdevice* device;
	ALCcontext* context;
	std::vector<sf::Sound*> sources;
	std::vector<sf::SoundBuffer*> buffers;
	std::vector<SoundEar*> listeners;
	std::vector<char*> soundBuffers;

	void init();
	static inline ALenum to_al_format(short channels, short samples);
	void removeUnusedSources();
	
};

#endif //SOUNDMANAGER_H