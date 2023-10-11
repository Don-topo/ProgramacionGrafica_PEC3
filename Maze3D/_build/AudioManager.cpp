#include "AudioManager.h"

AudioManager::AudioManager() {};

void AudioManager::InitAudio()
{
	InitAudioDevice();
	menuMusic = LoadMusicStream("resources/Audio/Title.mp3");
	level1Music = LoadMusicStream("resources/Audio/Level1.mp3");
	level2Music = LoadMusicStream("resources/Audio/Level2.mp3");
	level3Music = LoadMusicStream("resources/Audio/Level3.mp3");
	endingMusic = LoadMusicStream("resources/Audio/Ending.mp3");

	successSound = LoadSound("resources/Audio/Success.mp3");
}

void AudioManager::UnloadAudio()
{
	UnloadMusicStream(menuMusic);
	UnloadMusicStream(level1Music);
	UnloadMusicStream(level2Music);
	UnloadMusicStream(level3Music);
	UnloadMusicStream(endingMusic);

	UnloadSound(successSound);

	CloseAudioDevice();     // Close audio context
}

void AudioManager::PlayMusic(MusicType music)
{
	switch (music)
	{
	case MusicType::Menu:
		PlayMusicStream(menuMusic);
		break;
	case MusicType::Level1:
		PlayMusicStream(level1Music);
		break;
	case MusicType::Level2:
		PlayMusicStream(level2Music);
		break;
	case MusicType::Level3:
		PlayMusicStream(level3Music);
		break;
	case MusicType::Ending:
		PlayMusicStream(endingMusic);
		break;
	default:
		break;
	}
}

void AudioManager::UpdateMusic(MusicType music)
{
	switch (music)
	{
	case MusicType::Menu:
		UpdateMusicStream(menuMusic);
		break;
	case MusicType::Level1:
		UpdateMusicStream(level1Music);
		break;
	case MusicType::Level2:
		UpdateMusicStream(level2Music);
		break;
	case MusicType::Level3:
		UpdateMusicStream(level3Music);
		break;
	case MusicType::Ending:
		UpdateMusicStream(endingMusic);
		break;
	default:
		break;
	}	
}

void AudioManager::StopMusic(MusicType music)
{
	switch (music)
	{
	case MusicType::Menu:
		StopMusicStream(menuMusic);
		break;
	case MusicType::Level1:
		StopMusicStream(level1Music);
		break;
	case MusicType::Level2:
		StopMusicStream(level2Music);
		break;
	case MusicType::Level3:
		StopMusicStream(level3Music);
		break;
	case MusicType::Ending:
		StopMusicStream(endingMusic);
		break;
	default:
		break;
	}
}


void AudioManager::PlaySoundEffect(SoundType sound)
{
	switch (sound)
	{
	case SoundType::Success:
		PlaySound(successSound);
		break;
	default:
		break;
	}
}

void AudioManager::StopSoundEffect(SoundType sound)
{
	switch (sound)
	{
	case SoundType::Success:
		StopSound(successSound);
		break;
	default:
		break;
	}
}