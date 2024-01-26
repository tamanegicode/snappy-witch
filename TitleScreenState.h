#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "raylib.h"

class TitleScreenState : public GameState
{
public:
	TitleScreenState(int canvasWidth, int canvasHeight, GameStateManager& gameStateManager, int& maxScore);
	virtual void update(float deltaTime) override;
	virtual void render(float deltaTime) override;
	virtual void unloadAssets() override;
private:
	GameStateManager& m_GameStateManager;
	Texture background{ LoadTexture("assets/textures/titleScreen.png") };
	int m_CanvasWidth{};
	int m_CanvasHeight{};
	int& m_maxScore;
};