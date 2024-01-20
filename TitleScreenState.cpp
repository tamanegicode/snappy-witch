#include "TitleScreenState.h"
#include "PlayState.h"

TitleScreenState::TitleScreenState(int cW, int cH, GameStateManager& gSM) : canvasWidth(cW), canvasHeight(cH), gameStateManager(gSM)
{
}

void TitleScreenState::update(float deltaTime)
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		gameStateManager.setGameState(std::make_unique<PlayState>(canvasWidth, canvasHeight, gameStateManager));
	}
}

void TitleScreenState::render(float deltaTime)
{
	DrawTexture(background, 0, 0, WHITE);
}

void TitleScreenState::unloadAssets()
{
	UnloadTexture(background);
}