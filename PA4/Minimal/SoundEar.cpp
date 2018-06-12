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
	glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->forward = glm::vec3(glm::mat4(glm::mat3(orien)) * glm::vec4(forward, 1.0f));
	this->up = glm::vec3(glm::mat4(glm::mat3(orien)) * glm::vec4(up, 1.0f));
}

void SoundEar::setOrien(glm::vec3 forward, glm::vec3 up)
{
	this->forward = forward;
	this->up = up;
}

glm::vec3 SoundEar::getForward()
{
	return forward;
}

glm::vec3 SoundEar::getUp()
{
	return up;
}

ALuint SoundEar::getID()
{
	return listener;
}

glm::vec3 SoundEar::getPos()
{
	return pos;
}
