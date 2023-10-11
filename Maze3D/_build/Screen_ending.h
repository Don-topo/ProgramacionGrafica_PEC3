#ifndef SCREEN_ENDING_H
#define SCREEN_ENDING_H

#include "raylib.h"

class Screen_ending
{
public:
	void InitEndingScreen(void);
	void UpdateEndingScreen(void);
	void DrawEndingScreen(void);
	void UnloadEndingScreen(void);
	int FinishEndingScreen(void);
private:
	const char* winTitleText = "CONGRATULATIONS!";
	const char* loseMainTitleText = "Press Enter";
	int finishScreen;
};

#endif // !SCREEN_ENDING_H