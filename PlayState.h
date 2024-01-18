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
	PlayState(int canvasWidth, int canvasHeight, GameStateManager& gSM);
	virtual void update(float deltaTime) override;
	virtual void render(float deltaTime) override;
	virtual void unloadAssets() override;
private:
	GameStateManager& gameStateManager;
	int canvasWidth{};
	int canvasHeight{};
	Witch witch{};
	BackgroundLayer skyLayer{};
	BackgroundLayer cloudLayer{};
	BackgroundLayer trees1Layer{};
	BackgroundLayer trees2Layer{};
	BackgroundLayer bushLayer{};
	BackgroundLayer groundLayer{};

	BackgroundLayer* backgroundLayers[6]{
	&skyLayer,
	&cloudLayer,
	&trees1Layer,
	&trees2Layer,
	&bushLayer,
	&groundLayer
	};

	Texture obstacleTexture{};

	Obstacle obstacle{};
	Obstacle obstacle2{};

	Obstacle* obstacles[2]{
		&obstacle,
		&obstacle2
	};

	int calcNextObstacle(Obstacle* obstacles[], float witchPosition);

	int nextObstacleIndex{ calcNextObstacle(obstacles, witch.getPositionX()) };

	int score{ 0 };
	int maxScore{ 0 };
	bool collided{};
};