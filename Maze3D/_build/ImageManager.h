#pragma once
#include "raylib.h"

enum class ImageType {
	Level1 = 0,
	Level2,
	Level3,
	Atlas
};

class ImageManager
{
public:
	ImageManager();
	void InitImages();
	void UnloadImages();
	Image& GetImage(ImageType image);
private:
	Image Level1Image;
	Image Level2Image;
	Image Level3Image;
	Image AtlasImage;
};

