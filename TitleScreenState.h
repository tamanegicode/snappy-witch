#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "raylib.h"

class TitleScreenState : public GameState
{
public:
	TitleScreenState(int canvasWidth, int canvasHeight, GameStateManager& gSM);
	virtual void update(float deltaTime) override;
	virtual void render(float deltaTime) override;
	virtual void unloadAssets() override;
private:
	GameStateManager& gameStateManager;
	Texture background{};
	int canvasWidth{};
	int canvasHeight{};
};