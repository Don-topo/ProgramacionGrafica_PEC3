#include "raylib.h"
#include "GameManager.h"

int main() {

	const int width = 1020;
	const int height = 800;
	const char* windowTitle = "Maze3D";

	InitWindow(width, height, windowTitle);
	SetTargetFPS(60);

	GameManager& gameManager = GameManager::GetGameManager();
	gameManager.InitGame();

	while (!WindowShouldClose()) {
		// Update
		gameManager.UpdateFrame();		
		// Draw
		gameManager.DrawFrame();
	}

	gameManager.UnloadGame();
	CloseWindow();

	return 0;
}