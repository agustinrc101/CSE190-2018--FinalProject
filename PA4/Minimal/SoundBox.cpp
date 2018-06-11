#include "SoundBox.h"

SoundBox::SoundBox(ALuint source)
{
	this->source = source;
}

SoundBox::~SoundBox()
{
	source = 0;
	soundManager = NULL;
	pos = glm::vec3(0.0f);
}

void SoundBox::playSound(unsigned int sound)
{
	float newpos[] = { pos.x, pos.y, pos.z };
	soundManager->playSound(source, newpos, sound);
}

unsigned int SoundBox::loadSound(std::string file)
{
	return soundManager->loadSound(file);
}

void SoundBox::setPos(glm::vec3 pos)
{
	this->pos = pos;
}

void SoundBox::setPos(float x, float y, float z)
{
	pos = glm::vec3(x, y, z);
}

ALuint SoundBox::getID()
{
	return source;
}
