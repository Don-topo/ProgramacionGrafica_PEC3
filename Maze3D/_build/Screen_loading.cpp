#include "Screen_loading.h"
#include "GameManager.h"

void Screen_loading::InitLoadingScreen()
{
	finishScreen = 0;
	// Load the new level
	GameManager::GetGameManager().GetLevelManager().LoadLevel(GameManager::GetGameManager().GetNextLevel());
	screenSecondsRemaining = 180;
}

void Screen_loading::UpdateLoadingScreen()
{
	transAlpha += 0.01f;
	screenSecondsRemaining--;
	if (screenSecondsRemaining < 0) {
		// Ask gameManager wich is the next level
		finishScreen = GameManager::GetGameManager().GetNextLevel();
	}
}

void Screen_loading::DrawLoadingScreen(void)
{
	DrawText(loadingText, (GetScreenWidth() / 2) - 120, (GetScreenHeight() / 2), 36, WHITE);
}

void Screen_loading::UnloadLoadingScreen(void)
{
}

int Screen_loading::FinishLoadingScreen()
{
	return finishScreen;
}
