#include "Screen_gameplay3.h"
#include "GameManager.h"
#include <stdio.h>
#include <malloc.h>

void Screen_gameplay3::InitGameplay3Screen()
{
	SetCamera();
	finishScreen = 0;
	mapPosition = { 0.0f, 0.0f, 0.0f };  // Set model position
	mapPixels = GameManager::GetGameManager().GetLevelManager().GetCurrentMapPixels();
	cubicmap = GameManager::GetGameManager().GetLevelManager().GetCubicMap();
	model = GameManager::GetGameManager().GetLevelManager().GetCurrentLevelModel();
	currentTime = 10600;

	Object* objects = GameManager::GetGameManager().GetMeshManager().GetObjects();
	int numObjects = GameManager::GetGameManager().GetMeshManager().GetObjectCounter();

	models = (Model*)malloc(numObjects * sizeof(Model) * sizeof(Texture2D));

	for (int i = 0; i < numObjects; i++) {
		models[i] = GameManager::GetGameManager().GetModelManager().GetModel(objects[i].modelType);
		models[i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = GameManager::GetGameManager().GetTextureManager().GetTexture(objects[i].textureType);
	}
}

void Screen_gameplay3::UpdateGameplay3Screen()
{
	Vector3 oldCamPos = camera.position;
	UpdateCamera(&camera);
	CheckMove(oldCamPos);
	CheckIfEndLevelIsReached();
	UpdateTime();
}

void Screen_gameplay3::DrawGameplay3Screen()
{
	BeginMode3D(camera);
	PrintModels();
	EndMode3D();
	DrawText(numberstring, 0, 0, 36, WHITE);
}

void Screen_gameplay3::UnloadGameplay3Screen() 
{
	free(models);
}

int Screen_gameplay3::FinishGameplay3Screen()
{
	return finishScreen;
}

void Screen_gameplay3::CheckMove(Vector3 oldPosition)
{
	Vector2 playerPos = { camera.position.x, camera.position.z };
	float playerRadius = 0.1f;  // Collision radius (player is modelled as a cilinder for collision)
	int playerCellX = (int)(playerPos.x - mapPosition.x + 0.5f);
	int playerCellY = (int)(playerPos.y - mapPosition.z + 0.5f);
	// Out-of-limits security check
	if (playerCellX < 0) playerCellX = 0;
	else if (playerCellX >= imMap.width) playerCellX = imMap.width - 1;

	if (playerCellY < 0) playerCellY = 0;
	else if (playerCellY >= imMap.height) playerCellY = imMap.height - 1;

	// Check map collisions using image data and player position
	for (int y = 0; y < cubicmap.height; y++)
	{
		for (int x = 0; x < cubicmap.width; x++)
		{
			if ((mapPixels[y * cubicmap.width + x].r == 255 || mapPixels[y * cubicmap.width + x].r == 128) &&       // Collision: white pixel, only check R channel
				(CheckCollisionCircleRec(playerPos, playerRadius,
					Rectangle({ mapPosition.x - 0.5f + x, mapPosition.z - 0.5f + y, 1.0f, 1.0f })
				)))
			{
				// Collision detected, reset camera position
				camera.position = oldPosition;
			}
		}
	}
}

void Screen_gameplay3::SetCamera() {
	// Prepare camera
	camera = { 0 };
	if (GameManager::GetGameManager().GetPreviousLevel() >= GameManager::GetGameManager().GetCurrentLevel()) {
		camera.position = startPosition[0];
	}
	else {
		camera.position = startPosition[1];
	}

	camera.target = Vector3({ 0.0f, 1.8f, 0.0f });
	camera.up = Vector3({ 0.0f, 1.0f, 0.0f });
	camera.fovy = 60.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	SetCameraMode(camera, CAMERA_FIRST_PERSON);
}

void Screen_gameplay3::CheckIfEndLevelIsReached() {
	if (camera.position.x > 14.0f && camera.position.y > 0.5f && camera.position.z <= 0.0f) {
		finishScreen = 1;
	}
	if (camera.position.x > 14.0f && camera.position.y > 0.5f && camera.position.z > 15.0f) {
		finishScreen = 2;
	}
}

void Screen_gameplay3::UpdateTime() {
	currentTime--;
	sprintf(numberstring, "%02d:%02d", (currentTime / 60) / 60, currentTime % 3600 / 60);
	if (currentTime <= 0) Restart();
}

void Screen_gameplay3::Restart() {
	if (GameManager::GetGameManager().GetPreviousLevel() >= GameManager().GetGameManager().GetCurrentLevel()) {
		camera.position = startPosition[0];
	}
	else {
		camera.position = startPosition[1];
	}
	currentTime = 1600;
	// Play sound
	GameManager::GetGameManager().GetAudioManager().PlaySoundEffect(SoundType::Success);
}

void Screen_gameplay3::PrintModels() {
	DrawModel(model, mapPosition, 1.0f, WHITE);
	if (models != nullptr) {
		for (int i = 0; i < GameManager::GetGameManager().GetMeshManager().GetObjectCounter(); i++) {
			Vector3 test = GameManager::GetGameManager().GetMeshManager().GetObjects()[i].position;
			DrawModel(models[i], GameManager::GetGameManager().GetMeshManager().GetObjects()[i].position, 0.02f, WHITE);
		}
	}
}