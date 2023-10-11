#pragma once
#include "raylib.h"

enum class TextureType {
	Logo = 0,
	Title,
	Atlas,
	Level1,
	Level2,
	Level3,
	Castle,
	House,
	Well
};

class TextureManager
{
public:
	TextureManager();
	void InitTextures();
	void UnloadTextures();
	Texture2D& GetTexture(TextureType texture);
private:	
	Texture2D logoTexture;
	Texture2D titleTexture;
	Texture2D fullAtlasTexture;
	Image level1Image;
	Image level2Image;
	Image level3Image;
	Texture2D cubicMap1;
	Texture2D castleTexture;
	Texture2D houseTexture;
	Texture2D wellTexture;
};