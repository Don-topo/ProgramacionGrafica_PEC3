#include "ImageManager.h"

ImageManager::ImageManager(){}

void ImageManager::InitImages()
{
	Level1Image = LoadImage("resources/Level1.png");
	Level2Image = LoadImage("resources/Level2.png");
	Level3Image = LoadImage("resources/Level3.png");
	AtlasImage = LoadImage("resources/cubemap_atlas_full.png");
}

void ImageManager::UnloadImages()
{
	UnloadImage(Level1Image);
	UnloadImage(Level2Image);
	UnloadImage(Level3Image);
	UnloadImage(AtlasImage);
}

Image& ImageManager::GetImage(ImageType image)
{
	switch (image)
	{
	case ImageType::Level1:
		return Level1Image;
		break;
	case ImageType::Level2:
		return Level2Image;
		break;
	case ImageType::Level3:
		return Level3Image;
		break;
	case ImageType::Atlas:
		return AtlasImage;
		break;
	}
}
