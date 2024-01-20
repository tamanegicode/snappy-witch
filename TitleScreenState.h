#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "raylib.h"

class TitleScreenState : public GameState
{
public:
	TitleScreenState(int cW, int cH, GameStateManager& gSM);
	virtual void update(float deltaTime) override;
	virtual void render(float deltaTime) override;
	virtual void unloadAssets() override;
private:
	GameStateManager& gameStateManager;
	Texture background{ LoadTexture("assets/textures/titleScreen.png") };
	int canvasWidth{};
	int canvasHeight{};
};