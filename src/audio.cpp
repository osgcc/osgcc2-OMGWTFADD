
#include "main.h"
#include "audio.h"
#include "components.h"



Audio::Audio()
{
	music = NULL;
}

Audio::~Audio()
{
	if (!music)
	{
		Mix_FreeMusic(music);
	}
}

void Audio::Init()
{
		
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16SYS; /* 16-bit stereo */
	int audio_channels = 2;
	int audio_buffers = 2048;

	Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);
}

void Audio::LoadMusic(const char* fname)
{

	music=Mix_LoadMUS(fname);
	if(!music) {
		printf("Mix_LoadMUS(\"%s\"): %s\n", fname, Mix_GetError());
		return;
	}

    Mix_VolumeMusic(100);
}

void Audio::PlayMusic()
{
	// play music forever

	if(Mix_PlayMusic(music, -1)==-1) {
	printf("Mix_PlayMusic: %s\n", Mix_GetError());
		// well, there's no music, but most games don't break without music...
	}
}

void Audio::PlaySound(int soundIndex)
{
	if (soundIndex >= soundcount)
	{
		return;
	}

	Mix_PlayChannel(1, sounds[soundIndex], 0);
}


int Audio::LoadSound(const char *file)
{
	if (soundcount == NUM_SOUNDS)
	{
		return -1;
	}

	sounds[soundcount] = Mix_LoadWAV(file);

	if (!sounds[soundcount])
	{
		printf("Cannot load sound '%s': %s\n", file, Mix_GetError());
	}

	soundcount++;

	return 0;
}

Mix_Chunk* Audio::sounds[NUM_SOUNDS] = {0};
int Audio::soundcount = 0;
