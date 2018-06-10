#include "SoundManager.h"

SoundManager::SoundManager()
{
	init();
}

SoundManager::~SoundManager()
{
	delete device;
	delete context;
}

void SoundManager::loadSound(std::string file)
{
	char type[4];
	double size, chuncksize;
	short formatType, channels;
	double sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	double dataSize;
	FILE *fp = NULL;
	fp = fopen(file.c_str(), "rb");

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')
	{
		std::cerr << "No RIFF\n";
		return;
	}

	fread(&size, sizeof(double), 1, fp);
	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')
	{
		std::cerr << "not WAVE";
		return;
	}

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')
	{
		std::cerr << "not fmt \n";
		return;
	}

	fread(&chuncksize, sizeof(double), 1, fp);
	fread(&formatType, sizeof(short), 1, fp);
	fread(&channels, sizeof(short), 1, fp);
	fread(&sampleRate, sizeof(double), 1, fp);
	fread(&avgBytesPerSec, sizeof(double), 1, fp);
	fread(&bytesPerSample, sizeof(short), 1, fp);
	fread(&bitsPerSample, sizeof(short), 1, fp);

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')
	{
		std::cerr << "Missing DATA\n";
		return;
	}

	fread(&dataSize, sizeof(double), 1, fp);

	unsigned char* buf = new unsigned char[dataSize];
	fread(buf, sizeof(char), dataSize, fp);


	ALuint source;
	ALuint buffer;
	ALuint frequency = sampleRate;
	ALenum format = 0;

	alGenBuffers(1, &buffer);
	alGenSources(1, &source);

	alBufferData(buffer, to_al_format(channels, bitsPerSample),
		buf, dataSize, frequency);


	ALfloat sourcePos[] = { 0.0f, 0.0f, 0.0f };
	ALfloat sourceVel[] = { 0.0f, 0.0f, 0.0f };
	ALfloat listenerPos[] = { 0.0f, 0.0f, 0.0f };
	ALfloat listenerVel[] = { 0.0f, 0.0f, 0.0f };
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

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
	alSourcePlay(source);
	alSourcePlay(source);

}

void SoundManager::playSound()
{
	ALuint source;
	ALCenum error;

	alGenSources((ALuint)1, &source);
	error = alGetError();
	if (error != AL_NO_ERROR)
	{
		std::cerr << error << std::endl;
		return;
	}

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
	alSource3f(source, AL_POSITION, 0, 0, 0);
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


	ALuint buffer;

	alGenBuffers((ALuint)1, &buffer);
	error = alGetError();
	if (error != AL_NO_ERROR)
	{
		std::cerr << error << std::endl;
		return;
	}
}

void SoundManager::testing(std::string file)
{
	char type[4];
	double size, chuncksize;
	short formatType, channels;
	double sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	double dataSize;
	FILE *fp = NULL;
	fp = fopen(file.c_str(), "rb");

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')
	{
		std::cerr << "No RIFF\n";
		return;
	}

	fread(&size, sizeof(double), 1, fp);
	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')
	{
		std::cerr << "not WAVE";
		return;
	}

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')
	{
		std::cerr << "not fmt \n";
		return;
	}

	fread(&chuncksize, sizeof(double), 1, fp);
	fread(&formatType, sizeof(short), 1, fp);
	fread(&channels, sizeof(short), 1, fp);
	fread(&sampleRate, sizeof(double), 1, fp);
	fread(&avgBytesPerSec, sizeof(double), 1, fp);
	fread(&bytesPerSample, sizeof(short), 1, fp);
	fread(&bitsPerSample, sizeof(short), 1, fp);

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')
	{
		std::cerr << "Missing DATA\n";
		return;
	}

	fread(&dataSize, sizeof(double), 1, fp);

	unsigned char* buf = new unsigned char[dataSize];
	fread(buf, sizeof(char), dataSize, fp);


	ALuint source;
	ALuint buffer;
	ALuint frequency = sampleRate;
	ALenum format = 0;

	alGenBuffers(1, &buffer);
	alGenSources(1, &source);

	alBufferData(buffer, to_al_format(channels, bitsPerSample),
		buf, dataSize, frequency);


	ALfloat sourcePos[] = { 0.0f, 0.0f, 0.0f };
	ALfloat sourceVel[] = { 0.0f, 0.0f, 0.0f };
	ALfloat listenerPos[] = { 0.0f, 0.0f, 0.0f };
	ALfloat listenerVel[] = { 0.0f, 0.0f, 0.0f };
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

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

	ALint source_state;
	alSourcePlay(source);
	alGetSourcei(source, AL_SOURCE_STATE, &source_state);
	// check for errors
	while (source_state == AL_PLAYING) {
		alGetSourcei(source, AL_SOURCE_STATE, &source_state);
		// check for errors
	}
	//alSourcePause(source);
	//alSourceStop(source);

	fclose(fp);
	delete [] buf;
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);

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
			return AL_FORMAT_STEREO16;
		else
			return AL_FORMAT_MONO16;
	case 8:
		if (stereo)
			return AL_FORMAT_STEREO8;
		else
			return AL_FORMAT_MONO8;
	default:
		return -1;
	}
}
