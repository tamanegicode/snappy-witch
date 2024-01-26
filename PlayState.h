#pragma once
#include "GameState.h"
#include "Witch.h"
#include "BackgroundLayer.h"
#include "Obstacle.h"
#include "GameStateManager.h"
#include <stack>
#include <memory>

class PlayState : public GameState
{
public:
	PlayState(int canvasWidth, int canvasHeight, GameStateManager& gameStateManager, int& maxScore);
	virtual void update(float deltaTime) override;
	virtual void render(float deltaTime) override;
	virtual void unloadAssets() override;
private:
	GameStateManager& m_GameStateManager;
	int m_CanvasWidth{};
	int m_CanvasHeight{};
	Witch witch { m_CanvasHeight, 0.5f, 0.6f };

	std::unique_ptr<BackgroundLayer> backgroundLayers[6]{
	std::make_unique<BackgroundLayer>("assets/textures/background.png", 0, m_CanvasWidth, m_CanvasHeight),
	std::make_unique<BackgroundLayer>("assets/textures/clouds.png", 2, m_CanvasWidth, m_CanvasHeight),
	std::make_unique<BackgroundLayer>("assets/textures/trees1.png", 25, m_CanvasWidth, m_CanvasHeight, 72),
	std::make_unique<BackgroundLayer>("assets/textures/trees2.png", 50, m_CanvasWidth, m_CanvasHeight, 46),
	std::make_unique<BackgroundLayer>("assets/textures/bush.png", 100, m_CanvasWidth, m_CanvasHeight, 26),
	std::make_unique<BackgroundLayer>("assets/textures/ground.png", 100, m_CanvasWidth, m_CanvasHeight)
	};

	Texture obstacleTexture{ LoadTexture("assets/textures/obstacle.png") };

	std::unique_ptr <Obstacle> obstacles[2]{
		std::make_unique<Obstacle>(obstacleTexture, m_CanvasWidth, m_CanvasWidth, m_CanvasHeight, 0.8f, 1.0f),
		std::make_unique<Obstacle>(obstacleTexture, m_CanvasWidth + m_CanvasWidth / 2, m_CanvasWidth, m_CanvasHeight, 0.8f, 1.0f)
	};

	int calcNextObstacle(std::unique_ptr<Obstacle> obstacles[], float witchPosition);

	int nextObstacleIndex{ calcNextObstacle(obstacles, witch.getPositionX()) };

	int score{ 0 };
	int& m_MaxScore;
	bool collided{};
};