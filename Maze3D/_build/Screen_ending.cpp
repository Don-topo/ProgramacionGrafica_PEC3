#include "Screen_ending.h"
#include "GameManager.h"

void Screen_ending::InitEndingScreen(void) {
	finishScreen = 0;
}

void Screen_ending::UpdateEndingScreen(void) {
	if (IsKeyDown(KEY_ENTER)) finishScreen = 1;
}

void Screen_ending::DrawEndingScreen(void) {
	DrawText(winTitleText, GetScreenWidth() / 2 - 200, GetScreenHeight() / 2, 36, WHITE);
	DrawText(loseMainTitleText, GetScreenWidth() / 2 - 140, GetScreenHeight() / 2 + 150, 24, WHITE);
}

void Screen_ending::UnloadEndingScreen(void) {}

int Screen_ending::FinishEndingScreen(void) {
	return finishScreen;
}