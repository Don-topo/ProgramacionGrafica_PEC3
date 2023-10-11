#ifndef SCREEN_LOADING_H
#define SCREEN_LOADING_H
#include "raylib.h"

class Screen_loading
{
public:
	Screen_loading() {};
	void InitLoadingScreen();
	void UpdateLoadingScreen();
	void DrawLoadingScreen(void);
	void UnloadLoadingScreen(void);
	int FinishLoadingScreen();
private:
	int screenSecondsRemaining = 200;
	int finishScreen = 0;
	float transAlpha = 0.0f;
	char* loadingText = "Loading...";
};

#endif // !SCREEN_LOADING_H

