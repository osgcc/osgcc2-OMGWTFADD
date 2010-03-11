
#ifndef AUDIO_INCLUDED
#define AUDIO_INCLUDED

#define NUM_SOUNDS 10

class Audio
{
public:
	Audio();
	~Audio();

	void LoadMusic(const char* fname);
	void PlayMusic();

	void Init();

	void PlaySound(int soundIndex);

	int LoadSound(const char *file);
	
	// sounds
	static Mix_Chunk* sounds[NUM_SOUNDS];
	static int soundcount;

	// music file
	Mix_Music *music;
};

#endif //#ifndef AUDIO_INCLUDED
