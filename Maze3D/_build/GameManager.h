#pragma once
#include "AudioManager.h"
#include "TextureManager.h"
#include "Screen_title.h"
#include "Screen_logo.h"
#include "Screen_options.h"
#include "Screen_ending.h"
#include "Screen_gameplay.h"
#include "Screen_gameplay2.h"
#include "Screen_gameplay3.h"
#include "Screen_loading.h"
#include "MeshManager.h"
#include "LevelManager.h"
#include "ImageManager.h"
#include "ModelManager.h"


typedef enum GameScreen { LOGO = 0, TITLE, OPTIONS, LOADING, GAMEPLAY, GAMEPLAY2, GAMEPLAY3, ENDING } GameScreen;

class GameManager
{
public:
	GameManager();
	static GameManager& GetGameManager();
	TextureManager& GetTextureManager() { return textureManager; };
	AudioManager& GetAudioManager() { return audioManager; };
	MeshManager& GetMeshManager() { return meshManager; };
	ImageManager& GetImageManager() { return imageManager; };
	LevelManager& GetLevelManager() { return levelManager; };
	ModelManager& GetModelManager() { return modelManager; };
	int GetCurrentLevel() { return currentLevel; };
	int GetMaxLevel() { return maxLevel; };
	int IncreaseLevel() { currentLevel++; };
	int GetNextLevel() { return nextLevel; };
	int GetPreviousLevel() { return previousLevel; };
	void InitGame();
	void UpdateFrame();
	void DrawFrame();
	void UnloadGame();
	void RestartGame();
private:
	static GameManager* GameManager_Ptr;
	GameScreen currentScreen = GameScreen::LOGO;

	void ChangeToScreen(int screen);
	void TransitionToScreen(int screen);
	void UpdateTransition();
	void DrawTransition();
	void UpdateSound();

	float transAlpha = 0.0f;
	bool onTransition = false;
	bool transFadeOut = false;
	int transFromScreen = -1;
	int transToScreen = -1;
	int currentLevel = 1;
	int nextLevel = 2;
	int maxLevel;
	int previousLevel = 0;

	// Screens
	Screen_logo screenLogo;
	Screen_title screenTitle;
	Screen_options screenOptions;
	Screen_loading screenLoading;
	Screen_gameplay screenGameplay;
	Screen_gameplay2 screenGameplay2;
	Screen_gameplay3 screenGameplay3;
	Screen_ending screenEnding;

	// Managers
	TextureManager textureManager = TextureManager();
	AudioManager audioManager = AudioManager();
	MeshManager meshManager = MeshManager();
	ImageManager imageManager = ImageManager();
	LevelManager levelManager = LevelManager();
	ModelManager modelManager = ModelManager();

};