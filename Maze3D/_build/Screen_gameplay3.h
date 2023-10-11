#ifndef SCREEN_GAMEPLAY3_H
#define SCREEN_GAMEPLAY3_H
#include "raylib.h"
#include <climits>

class Screen_gameplay3
{
public:
	Screen_gameplay3() {};
	void InitGameplay3Screen();
	void UpdateGameplay3Screen();
	void DrawGameplay3Screen();
	void UnloadGameplay3Screen();
	int FinishGameplay3Screen();

private:
	int finishScreen = 0;
	void CheckMove(Vector3 oldPosition);
	void SetCamera();
	void CheckIfEndLevelIsReached();
	void UpdateTime();
	void Restart();
	void PrintModels();
	int currentTime;
	char numberstring[(sizeof(int) * CHAR_BIT)];
	Vector3 startPosition[2] = { { 14.0f, 0.5f, 14.0f },{ 15.0f, 0.5f, 1.0f } };
	Mesh mesh;
	Model model;
	Vector3 mapPosition;
	Camera3D camera;
	Color* mapPixels;
	Texture2D cubicmap;
	Image imMap;
	Model* models = nullptr;
};

#endif // !SCREEN_GAMEPLAY_H