#ifndef SCREEN_OPTIONS_H
#define SCREEN_OPTIONS_H


#include "raylib.h"


class Screen_options
{

public:
	void InitOptionsScreen(void);
	void UpdateOptionsScreen(void);
	void DrawOptionsScreen(void);
	void UnloadOptionsScreen(void);
	int FinishOptionsScreen(void);
private:
	int finishScreen;
	const char* optionsMovementText = "To move the player use direction keys or A,D,W,S.";
	const char* optionsDescriptionText = "You can look around moving the mouse.";
	const char* optionsDescriptionText2 = "The game has three levels:";
	const char* optionsWinText = "You must find the maze exit before the time runs out.";
	const char* optionsExitText = "Press 'o' to go to the main menu";
};

#endif // !SCREEN_OPTIONS_H