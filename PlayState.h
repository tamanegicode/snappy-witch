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
	PlayState(int cW, int cH, GameStateManager& gSM);
	virtual void update(float deltaTime) override;
	virtual void render(float deltaTime) override;
	virtual void unloadAssets() override;
private:
	GameStateManager& gameStateManager;
	int canvasWidth{};
	int canvasHeight{};
	Witch witch { canvasHeight, 0.5f, 0.6f };

	std::unique_ptr<BackgroundLayer> backgroundLayers[6]{
	std::make_unique<BackgroundLayer>(LoadTexture("assets/textures/background.png"), 0, canvasWidth, canvasHeight),
	std::make_unique<BackgroundLayer>(LoadTexture("assets/textures/clouds.png"), 2, canvasWidth, canvasHeight),
	std::make_unique<BackgroundLayer>(LoadTexture("assets/textures/trees1.png"), 25, canvasWidth, canvasHeight, 72),
	std::make_unique<BackgroundLayer>(LoadTexture("assets/textures/trees2.png"), 50, canvasWidth, canvasHeight, 48),
	std::make_unique<BackgroundLayer>(LoadTexture("assets/textures/bush.png"), 100, canvasWidth, canvasHeight, 26),
	std::make_unique<BackgroundLayer>(LoadTexture("assets/textures/ground.png"), 100, canvasWidth, canvasHeight)
	};

	Texture obstacleTexture{ LoadTexture("assets/textures/obstacle.png") };

	Obstacle obstacle{ obstacleTexture, canvasWidth, canvasWidth, canvasHeight, 0.8f, 1.0f };
	Obstacle obstacle2{ obstacleTexture, canvasWidth + canvasWidth / 2, canvasWidth, canvasHeight, 0.8f, 1.0f };

	std::unique_ptr <Obstacle> obstacles[2]{
		std::make_unique<Obstacle>(obstacleTexture, canvasWidth, canvasWidth, canvasHeight, 0.8f, 1.0f),
		std::make_unique<Obstacle>(obstacleTexture, canvasWidth + canvasWidth / 2, canvasWidth, canvasHeight, 0.8f, 1.0f)
	};

	int calcNextObstacle(std::unique_ptr<Obstacle> obstacles[], float witchPosition);

	int nextObstacleIndex{ calcNextObstacle(obstacles, witch.getPositionX()) };

	int score{ 0 };
	int maxScore{ 0 };
	bool collided{};
};