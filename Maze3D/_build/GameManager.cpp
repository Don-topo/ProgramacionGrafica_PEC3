#include "GameManager.h"

GameManager* GameManager::GameManager_Ptr = nullptr;

GameManager::GameManager(){}

GameManager& GameManager::GetGameManager()
{
	if (GameManager_Ptr == nullptr) {
		GameManager_Ptr = new GameManager();
	}
	return *GameManager_Ptr;
}

void GameManager::InitGame()
{
    screenLogo = Screen_logo();
    screenTitle = Screen_title();
    screenOptions = Screen_options();
    screenGameplay = Screen_gameplay();
    screenGameplay2 = Screen_gameplay2();
    screenGameplay3 = Screen_gameplay3();
    screenEnding = Screen_ending();
    screenLoading = Screen_loading();

    textureManager.InitTextures();
    imageManager.InitImages();
    audioManager.InitAudio();
    modelManager.InitModels();

    currentScreen = LOGO;
    currentLevel = 1;
    previousLevel = 0;
    maxLevel = 1;
    nextLevel = 1;
    screenLogo.InitLogoScreen();
}

void GameManager::UpdateFrame()
{
    if (!onTransition)
    {
        switch (currentScreen)
        {
        case LOGO:
        {
            screenLogo.UpdateLogoScreen();
            if (screenLogo.FinishLogoScreen()) TransitionToScreen(TITLE);

        } break;
        case TITLE:
        {
            screenTitle.UpdateTitleScreen();
            if (screenTitle.FinishTitleScreen() == 1) TransitionToScreen(OPTIONS);
            else if (screenTitle.FinishTitleScreen() == 2) {
                currentLevel = 1;
                previousLevel = 0;
                maxLevel = 1;
                nextLevel = 1;
                TransitionToScreen(LOADING);
            }

        } break;
        case OPTIONS:
        {
            screenOptions.UpdateOptionsScreen();
            if (screenOptions.FinishOptionsScreen() == 1) TransitionToScreen(TITLE);

        } break;
        case LOADING:
            screenLoading.UpdateLoadingScreen();
            switch (screenLoading.FinishLoadingScreen())
            {
            case 1:     
                TransitionToScreen(GAMEPLAY);
                break;
            case 2:    
                TransitionToScreen(GAMEPLAY2);
                break;
            case 3:               
                TransitionToScreen(GAMEPLAY3);
                break;
            default:
                break;
            }
            break;
        case GAMEPLAY:
        {
            screenGameplay.UpdateGameplayScreen();            
            if (screenGameplay.FinishGameplayScreen() == 1)
            {
                nextLevel = 2;
                previousLevel = 1;
                TransitionToScreen(LOADING);
            }
            if (screenGameplay.FinishGameplayScreen() == 2) 
            {
                previousLevel = 2;
                nextLevel = 1;
                TransitionToScreen(LOADING);
            }

        } break;
        case GAMEPLAY2:
            screenGameplay2.UpdateGameplay2Screen();
            if (screenGameplay2.FinishGameplay2Screen() == 1)
            {
                previousLevel = 2;
                nextLevel = 3;
                TransitionToScreen(LOADING);
            }
            if (screenGameplay2.FinishGameplay2Screen() == 2) 
            {
                previousLevel = 2;
                nextLevel = 1;
                TransitionToScreen(LOADING);
            }
            break;
        case GAMEPLAY3:
            screenGameplay3.UpdateGameplay3Screen();
            if (screenGameplay3.FinishGameplay3Screen() == 1) 
            {
                nextLevel = 1;
                TransitionToScreen(ENDING);
            }
            if (screenGameplay3.FinishGameplay3Screen() == 2)
            {
                previousLevel = 3;
                nextLevel = 2;
                TransitionToScreen(LOADING);
            }
        case ENDING:
        {
            screenEnding.UpdateEndingScreen();
            if (screenEnding.FinishEndingScreen() == 1) TransitionToScreen(TITLE);

        } break;
        default: break;
        }
    }
    else UpdateTransition();    // Update transition (fade-in, fade-out)
    //----------------------------------------------------------------------------------

    UpdateSound();
}

void GameManager::DrawFrame()
{
    BeginDrawing();

    ClearBackground(BLACK);

    switch (currentScreen)
    {
        case LOGO: screenLogo.DrawLogoScreen(); break;
        case TITLE: screenTitle.DrawTitleScreen(); break;
        case OPTIONS: screenOptions.DrawOptionsScreen(); break;      
        case LOADING: screenLoading.DrawLoadingScreen(); break;
        case GAMEPLAY: screenGameplay.DrawGameplayScreen(); break;
        case GAMEPLAY2: screenGameplay2.DrawGameplay2Screen(); break;
        case GAMEPLAY3: screenGameplay3.DrawGameplay3Screen(); break;
        case ENDING: screenEnding.DrawEndingScreen(); break;
        default: break;
    }

    // Draw full screen rectangle in front of everything
    if (onTransition) DrawTransition();


    EndDrawing();
}

void GameManager::UnloadGame()
{
    switch (currentScreen)
    {
    case LOGO: screenLogo.UnloadLogoScreen(); break;
    case TITLE: screenTitle.UnloadTitleScreen(); break;
    case GAMEPLAY: screenGameplay.UnloadGameplayScreen(); break;
    case GAMEPLAY2: screenGameplay2.UnloadGameplay2Screen(); break;
    case GAMEPLAY3: screenGameplay3.UnloadGameplay3Screen(); break;
    case LOADING: screenLoading.UnloadLoadingScreen(); break;
    case ENDING: screenEnding.UnloadEndingScreen(); break;
    default: break;
    }
    
    textureManager.UnloadTextures();
    audioManager.UnloadAudio();
    imageManager.UnloadImages();
    modelManager.UnloadModels();

}

void GameManager::ChangeToScreen(int screen)
{
    // Unload current screen
    switch (currentScreen)
    {
    case LOGO: screenLogo.UnloadLogoScreen(); break;
    case TITLE: screenTitle.UnloadTitleScreen(); break;
    case GAMEPLAY: screenGameplay.UnloadGameplayScreen(); break;
    case GAMEPLAY2: screenGameplay2.UnloadGameplay2Screen(); break;
    case GAMEPLAY3: screenGameplay3.UnloadGameplay3Screen(); break;
    case LOADING: screenLoading.UnloadLoadingScreen(); break;
    case ENDING: screenEnding.UnloadEndingScreen(); break;
    default: break;
    }

    // Init next screen
    switch (screen)
    {
    case LOGO: screenLogo.InitLogoScreen(); break;
    case TITLE: 
        screenTitle.InitTitleScreen(); 
        audioManager.PlayMusic(MusicType::Menu);
        break;
    case LOADING: screenLoading.InitLoadingScreen(); break;
    case GAMEPLAY:
    {
        audioManager.PlayMusic(MusicType::Level1);
        screenGameplay.InitGameplayScreen();       
        break;
    }
    case GAMEPLAY2:
        screenGameplay2.InitGameplay2Screen();
        audioManager.PlayMusic(MusicType::Level2);
        break;
    case GAMEPLAY3:
        screenGameplay3.InitGameplay3Screen();
        audioManager.PlayMusic(MusicType::Level3);
        break;
    case ENDING:
    {
        screenEnding.InitEndingScreen();
        audioManager.PlayMusic(MusicType::Ending);
        break;
    }
    default: break;
    }

    currentScreen = (GameScreen)screen;
}

// Request transition to next screen
void GameManager::TransitionToScreen(int screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

// Update transition effect (fade-in, fade-out)
void GameManager::UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            switch (transFromScreen)
            {
            case LOGO: screenLogo.UnloadLogoScreen(); break;
            case TITLE: screenTitle.UnloadTitleScreen(); break;
            case OPTIONS: screenOptions.UnloadOptionsScreen(); break;
            case LOADING: screenLoading.UnloadLoadingScreen(); break;
            case GAMEPLAY: screenGameplay.UnloadGameplayScreen(); break;
            case GAMEPLAY2: screenGameplay2.UnloadGameplay2Screen(); break;
            case GAMEPLAY3: screenGameplay3.UnloadGameplay3Screen(); break;
            case ENDING: screenEnding.UnloadEndingScreen(); break;
            default: break;
            }

            // Load next screen
            switch (transToScreen)
            {
            case LOGO: screenLogo.InitLogoScreen(); break;
            case TITLE: 
                screenTitle.InitTitleScreen();
                audioManager.PlayMusic(MusicType::Menu);
                break;
            case LOADING: screenLoading.InitLoadingScreen(); break;
            case GAMEPLAY: 
                screenGameplay.InitGameplayScreen();
                audioManager.PlayMusic(MusicType::Level1);
                break;
            case GAMEPLAY2: 
                screenGameplay2.InitGameplay2Screen(); 
                audioManager.PlayMusic(MusicType::Level2);
                break;
            case GAMEPLAY3: 
                screenGameplay3.InitGameplay3Screen(); 
                audioManager.PlayMusic(MusicType::Level3);
                break;
            case ENDING: 
                screenEnding.InitEndingScreen(); 
                audioManager.PlayMusic(MusicType::Ending);
                break;
            case OPTIONS: screenOptions.InitOptionsScreen(); break;
            default: break;
            }

            currentScreen = (GameScreen)transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = -1;
        }
    }
}

// Draw transition effect (full-screen rectangle)
void GameManager::DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

void GameManager::UpdateSound()
{
    switch (currentScreen)
    {
    case LOGO:
        break;
    case TITLE:
        audioManager.UpdateMusic(MusicType::Menu);
        break;
    case OPTIONS:
        audioManager.UpdateMusic(MusicType::Menu);
        break;
    case LOADING:
        break;
    case GAMEPLAY:
        audioManager.UpdateMusic(MusicType::Level1);
        break;
    case GAMEPLAY2:
        audioManager.UpdateMusic(MusicType::Level2);
        break;
    case GAMEPLAY3:
        audioManager.UpdateMusic(MusicType::Level3);
        break;
    case ENDING:
        audioManager.UpdateMusic(MusicType::Ending);
        break;
    default:
        break;
    }
}
