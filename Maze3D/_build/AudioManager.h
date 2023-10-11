#pragma once

#include "raylib.h"

enum class SoundType {
	Success,
};

enum class MusicType {
	Menu,
	Level1,
	Level2,
	Level3,
	Ending
};

class AudioManager
{
public:
	AudioManager();
	void InitAudio();
	void UnloadAudio();
	void PlayMusic(MusicType music);
	void UpdateMusic(MusicType music);
	void StopMusic(MusicType music);
	void PlaySoundEffect(SoundType sound);
	void StopSoundEffect(SoundType sound);
private:
	Music menuMusic;
	Music level1Music;
	Music level2Music;
	Music level3Music;
	Music endingMusic;

	Sound successSound;
};
