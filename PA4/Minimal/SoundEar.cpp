#include "SoundEar.h"

SoundEar::SoundEar(ALuint source, SoundManager* soundManager)
{
	this->listener = source;
	this->soundManager = soundManager;
}

SoundEar::~SoundEar()
{
	listener = 0;
	soundManager = NULL;
	pos = glm::vec3(0.0f);
}

void SoundEar::setPos(glm::vec3 pos)
{
	this->pos = pos;
}

void SoundEar::setPos(float x, float y, float z)
{
	pos = glm::vec3(x, y, z);
}

void SoundEar::setOrien(glm::mat4 orien)
{
	this->orien = orien;
}

ALuint SoundEar::getID()
{
	return listener;
}

glm::vec3 SoundEar::getPos()
{
	return pos;
}

glm::mat4 SoundEar::getOrien()
{
	return orien;
}
