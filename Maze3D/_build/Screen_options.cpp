#include "Screen_options.h"

void Screen_options::InitOptionsScreen(void) {
	finishScreen = 0;
}

void Screen_options::UpdateOptionsScreen(void) {
	if (IsKeyDown(KEY_O)) finishScreen = 1;
}

void Screen_options::DrawOptionsScreen(void) {
	DrawText(optionsMovementText, GetScreenWidth() / 4 - sizeof(optionsMovementText) * 10, 80, 24, WHITE);
	DrawText(optionsDescriptionText, GetScreenWidth() / 2 - 320, 120, 24, WHITE);
	DrawText(optionsDescriptionText2, GetScreenWidth() / 2 - 250, 160, 24, WHITE);
	DrawText(optionsWinText, GetScreenWidth() / 4 - 80, 200, 24, WHITE);
	DrawText(optionsExitText, GetScreenWidth() / 4 - 20, 240, 24, WHITE);
}

void Screen_options::UnloadOptionsScreen(void) {
	finishScreen = 0;
}

int Screen_options::FinishOptionsScreen(void) {
	return finishScreen;
}