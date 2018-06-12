#include "SoundManager.h"

SoundManager::SoundManager()
{
	init();
}

SoundManager::~SoundManager()
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
	/*for (size_t i = 0; i < sources.size(); ++i)
	{
		ALuint source = sources[i]->getID();
		alDeleteSources(1, &source);
	}*/
	for (size_t i = 0; i < listeners.size(); ++i)
	{
		ALuint listener = listeners[i]->getID();
		alDeleteSources(1, &listener);
	}
	for (size_t i = 0; i < buffers.size(); ++i)
	{
		delete buffers[i];
		buffers[i] = NULL;
	}
	for (size_t i = 0; i < soundBuffers.size(); ++i)
	{
		delete[] soundBuffers[i];
		soundBuffers[i] = NULL;
	}
	/*for (size_t i = 0; i < sources.size(); ++i)
	{
		delete sources[i];
		sources[i] = NULL;
	}*/
	for (size_t i = 0; i < listeners.size(); ++i)
	{
		delete listeners[i];
		listeners[i] = NULL;
	}
}

unsigned int SoundManager::loadSound(std::string file)
{
	sf::SoundBuffer* buffer = new sf::SoundBuffer();
	buffers.push_back(buffer);
	if (!buffers.back()->loadFromFile(file))
	{
		std::cerr << file << std::endl;
		return 0;
	}
	return buffers.size() - 1;
}

/*void SoundManager::playSound(ALuint source, ALfloat* sourcePos, ALint buffer)
{
	ALCenum error;

	ALfloat sourceVel[] = { 0.0f, 0.0f, 0.0f };
	glm::vec3 listenerVec = glm::vec3(0.0f);
	ALfloat listenerPos[3] = { 0.0f, 0.0f, 0.0f };
	ALfloat listenerVel[] = { 0.0f, 0.0f, 0.0f };
	ALfloat listenerOri[6];
	glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	for(size_t i = 0; i < listeners.size(); ++i)
	{
		listenerVec = listeners[i]->getPos();
		// correct
		//listenerPos[0] = listenerVec.x;
		//listenerPos[1] = listenerVec.y;
		//listenerPos[2] = listenerVec.z;
		//std::cerr << "source pos\n";
		//std::cerr << sourcePos[0] << " " << sourcePos[1] << " " << sourcePos[2] << std::endl;

		//forward = listeners[i]->getForward();
		//up = listeners[i]->getUp();
		//std::cerr << "forward pos\n";
		//UsefulFunctions::printVector(listenerVec + forward);
		//UsefulFunctions::printVector(newup);
		listenerOri[6] = forward.x;
		listenerOri[6] = forward.y;
		listenerOri[6] = forward.z;
		listenerOri[6] = up.x;
		listenerOri[6] = up.y;
		listenerOri[6] = up.z;

		//Listener
		alListenerfv(AL_POSITION, listenerPos);
		// check for errors
		alListenerfv(AL_VELOCITY, listenerVel);
		// check for errors
		alListenerfv(AL_ORIENTATION, listenerOri);
		// check for errors

		//Source
		alSourcei(source, AL_BUFFER, buffer);
		alSourcef(source, AL_PITCH, 1);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cerr << error << std::endl;
			return;
		}
		alSourcef(source, AL_GAIN, 1);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cerr << error << std::endl;
			return;
		}
		alSourcefv(source, AL_POSITION, sourcePos);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cerr << error << std::endl;
			return;
		}
		alSource3f(source, AL_VELOCITY, 0, 0, 0);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cerr << error << std::endl;
			return;
		}
		alSourcei(source, AL_LOOPING, AL_FALSE);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cerr << error << std::endl;
			return;
		}
		alSourcei(source, AL_LOOPING, AL_FALSE);

		alSourcePlay(source);
	}

}*/

void SoundManager::playSound(glm::vec3 sourcePos, unsigned int buffer, float volume)
{
	sf::Sound* sound = new sf::Sound();
	sources.push_back(sound);

	glm::vec3 listenerPos = glm::vec3(0.0f);
	glm::vec3 listenerForward = glm::vec3(0.0f);
	glm::vec3 listenerUp = glm::vec3(0.0f);
	for (size_t i = 0; i < listeners.size(); ++i)
	{
		listenerPos = listeners[i]->getPos();
		listenerForward = listeners[i]->getForward();
		listenerUp = listeners[i]->getUp();
		sf::Listener::setPosition(listenerPos.x, listenerPos.y, listenerPos.z);
		sf::Listener::setDirection(listenerForward.x, listenerForward.y, listenerForward.z);
		sf::Listener::setUpVector(listenerUp.x, listenerUp.y, listenerUp.z);
		sources.back()->setPosition(sourcePos.x, sourcePos.y, sourcePos.z);

		sources.back()->setBuffer(*buffers[buffer]);
		sources.back()->play();
	}
}

SoundBox* SoundManager::createSource()
{
	return new SoundBox(this);
}

SoundEar* SoundManager::createListener()
{
	ALuint listener;
	alGenSources(1, &listener);
	listeners.push_back(new SoundEar(listener, this));
	return listeners.back();
}

void SoundManager::testing(std::string file)
{
	sf::SoundBuffer* buffer = new sf::SoundBuffer();
	buffers.push_back(buffer);
	if (!buffers.back()->loadFromFile(file))
	{
		std::cerr << file << std::endl;
		return;
	}

	sf::Sound* sound = new sf::Sound();
	sources.push_back(sound);

	sf::Listener::setPosition(0.f, 0.f, 0.f);
	sf::Listener::setDirection(0.f, 0.f, -1.f);
	sf::Listener::setUpVector(0.f, 1.f, 0.f);
	sources.back()->setPosition(-1.f, 0.f, 0.f);

	sources.back()->setBuffer(*buffer);
	sources.back()->play();

	//while (sound.getStatus() == sf::Sound::Playing)
	{
	}


}

void SoundManager::testing2(ALuint source, ALfloat* sourcePos, ALint buffer1, std::string file)
{
	char type[4];
	int size, chuncksize;
	short formatType, channels;
	unsigned int sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	unsigned int dataSize;
	FILE *fp = NULL;
	fp = fopen(file.c_str(), "rb");

	fread(type, BYTE, 4, fp);
	if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')
	{
		std::cerr << "No RIFF\n";
		return;
	}

	fread(&size, FOURBYTE, 1, fp);
	fread(type, BYTE, 4, fp);
	if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')
	{
		std::cerr << "not WAVE\n";
		return;
	}

	fread(type, BYTE, 4, fp);
	if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')
	{
		std::cerr << "not fmt \n";
		return;
	}

	fread(&chuncksize, FOURBYTE, 1, fp);
	fread(&formatType, TWOBYTE, 1, fp);
	fread(&channels, TWOBYTE, 1, fp);
	fread(&sampleRate, FOURBYTE, 1, fp);
	fread(&avgBytesPerSec, FOURBYTE, 1, fp);
	fread(&bytesPerSample, TWOBYTE, 1, fp);
	fread(&bitsPerSample, TWOBYTE, 1, fp);

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')
	{
		std::cerr << "Missing DATA\n";
		return;
	}

	fread(&dataSize, FOURBYTE, 1, fp);

	unsigned char* buf = new unsigned char[dataSize];
	fread(buf, sizeof(char), dataSize, fp);

	ALuint buffer;
	ALuint frequency = sampleRate;
	ALenum format = 0;

	alGenBuffers(1, &buffer);
	alGenSources(1, &source);

	alBufferData(buffer, to_al_format(channels, bitsPerSample),
		buf, dataSize, frequency);


	ALfloat sourceVel[] = { 0.0f, 0.0f, 0.0f };
	glm::vec3 listenerVec = glm::vec3(0.0f);
	ALfloat listenerPos[3];
	ALfloat listenerVel[] = { 0.0f, 0.0f, 0.0f };
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

	for (size_t i = 0; i < listeners.size(); ++i)
	{
		listenerVec = listeners[i]->getPos();
		listenerPos[0] = listenerVec.x;
		listenerPos[1] = listenerVec.y;
		listenerPos[2] = listenerVec.z;
		//Listener
		alListenerfv(AL_POSITION, listenerPos);
		// check for errors
		alListenerfv(AL_VELOCITY, listenerVel);
		// check for errors
		alListenerfv(AL_ORIENTATION, listenerOri);
		// check for errors

		//Source
		alSourcei(source, AL_BUFFER, buffer);
		alSourcef(source, AL_PITCH, 1.0f);
		alSourcef(source, AL_GAIN, 1.0f);
		alSourcefv(source, AL_POSITION, sourcePos);
		alSourcefv(source, AL_VELOCITY, sourceVel);
		alSourcei(source, AL_LOOPING, AL_FALSE);

		alSourcePlay(source);
	}

	//alSourcePause(source);
	//alSourceStop(source);

	fclose(fp);
	delete[] buf;
	alDeleteBuffers(1, &buffer);

}

void SoundManager::update()
{
	removeUnusedSources();
}

void SoundManager::init()
{
	ALCenum error;
	device = alcOpenDevice(NULL);
	if (!device)
	{
		std::cerr << "Failed to open audio device.\n";
		return;
	}

	alGetError();
	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context))
	{
		std::cerr << "Failed to create context.\n";
		return;
	}

	error = alGetError();
	if (error != AL_NO_ERROR)
	{
		std::cerr << error << std::endl;
		return;
	}
}

ALenum SoundManager::to_al_format(short channels, short samples)
{
	bool stereo = (channels > 1);

	switch (samples) {
	case 16:
		if (stereo)
		{
			//std::cerr << "Stereo 16\n";
			return AL_FORMAT_STEREO16;
		}
		else
		{
			//std::cerr << "Mono 16\n";
			return AL_FORMAT_MONO16;
		}
	case 8:
		if (stereo)
		{
			//std::cerr << "Stereo 8\n";
			return AL_FORMAT_STEREO8;
		}
		else
		{
			//std::cerr << "Mono 8\n";
			return AL_FORMAT_MONO8;
		}
	default:
		return -1;
	}
}

void SoundManager::removeUnusedSources()
{
	for (int i = 0; i < sources.size(); ++i)
	{
		if (sources[i]->getStatus() != sf::Sound::Playing)
		{
			delete sources[i];
			sources[i] = NULL;
			sources.erase(sources.begin() + i);
		}
	}
}
