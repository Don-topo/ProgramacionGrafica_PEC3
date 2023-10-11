#pragma once
#include "raylib.h"

class LevelManager
{
public:
	LevelManager(){};
	void LoadLevel(int level);
	Model GetCurrentLevelModel() { return currentLevelModel; };
	Color* GetCurrentMapPixels() { return mapPixels; };
	Texture2D GetCubicMap() { return cubicMap; };
private:
	Image levelImage;
	Model currentLevelModel;
	Mesh currentMesh;
	Texture2D cubicMap;
	Color* mapPixels;
};

