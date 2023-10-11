#include "LevelManager.h"
#include "GameManager.h"

void LevelManager::LoadLevel(int level)
{
	switch (level)
	{
	case 1:
		levelImage = GameManager::GetGameManager().GetImageManager().GetImage(ImageType::Level1);
		break;
	case 2:
		levelImage = GameManager::GetGameManager().GetImageManager().GetImage(ImageType::Level2);
		break;
	case 3:
		levelImage = GameManager::GetGameManager().GetImageManager().GetImage(ImageType::Level3);
		break;
	default:
		break;
	}	

	cubicMap = LoadTextureFromImage(levelImage);
	currentMesh = GameManager::GetGameManager().GetMeshManager().GenerateMesh(levelImage, Vector3{ 1.0f, 1.0f, 1.0f });
	currentLevelModel = LoadModelFromMesh(currentMesh);
	currentLevelModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = GameManager::GetGameManager().GetTextureManager().GetTexture(TextureType::Atlas);
	mapPixels = LoadImageColors(levelImage);
}
