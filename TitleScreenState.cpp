#include "TitleScreenState.h"
#include "PlayState.h"

TitleScreenState::TitleScreenState(int canvasWidth, int canvasHeight, GameStateManager& gameStateManager)
	: m_CanvasWidth(canvasWidth), m_CanvasHeight(canvasHeight), m_GameStateManager(gameStateManager)
{
}

void TitleScreenState::update(float deltaTime)
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		m_GameStateManager.setGameState(std::make_unique<PlayState>(m_CanvasWidth, m_CanvasHeight, m_GameStateManager));
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