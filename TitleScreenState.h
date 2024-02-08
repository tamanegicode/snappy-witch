#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "raylib.h"
#include "BackgroundLayer.h"
#include "Witch.h"

class TitleScreenState : public GameState
{
public:
	TitleScreenState(int canvasWidth, int canvasHeight, GameStateManager& gameStateManager, int& maxScore);
	virtual void update(float deltaTime) override;
	virtual void render(float deltaTime) override;
	virtual void unloadAssets() override;
private:
	GameStateManager& m_GameStateManager;
	int m_CanvasWidth{};
	int m_CanvasHeight{};
	int& m_MaxScore;
	Texture sky{ LoadTexture("assets/textures/titleScreenSky.png") };
	Texture trees1{ LoadTexture("assets/textures/titleScreenTrees1.png") };
	Texture trees2{ LoadTexture("assets/textures/titleScreenTrees2.png") };
	Texture thorns{ LoadTexture("assets/textures/titleScreenThorns.png") };
	Texture logo{ LoadTexture("assets/textures/titleScreenLogo.png") };
	Texture witch{ LoadTexture("assets/textures/spritesheetWitch.png") };
	Texture bat{ LoadTexture("assets/textures/bat.png") };
	Texture playButtonDefault{ LoadTexture("assets/textures/titleScreenButtonDefault.png") };
	Texture playButtonHover{ LoadTexture("assets/textures/titleScreenButtonHover.png") };
	Texture playButtonPressed{ LoadTexture("assets/textures/titleScreenButtonPressed.png") };
	Vector2 playButtonPosition{ static_cast<float>(m_CanvasWidth / 2 - playButtonDefault.width / 2), 150 };
	Rectangle playButtonCollisionRectangle{ playButtonPosition.x, playButtonPosition.y, static_cast<float>(playButtonDefault.width), static_cast<float>(playButtonDefault.height) };
	bool isMouseOverPlayButton{ false };

	BackgroundLayer clouds { "assets/textures/titleScreenClouds.png", 2, m_CanvasWidth, m_CanvasHeight };

	Color fadeColor{ 0, 0, 0, 255 };
	float fadeSpeed{ 300.0f };
	bool fadeIn{ true };
	
	int witchFrameToDraw{ 0 };
	int witchFrameNumber{ 3 };
	float witchFrameTime{ 0.3f };
	float witchAnimationTime{ 0.0f };

	int batFrameToDraw{ 0 };
	int batFrameNumber{ 6 };
	float batFrameTime{ 0.1f };
	float batAnimationTime{ 0.0f };
};