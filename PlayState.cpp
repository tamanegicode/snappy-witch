#include "PlayState.h"

PlayState::PlayState(int canvasWidth, int canvasHeight, GameStateManager& gSM) : gameStateManager(gSM)
{
	this->canvasWidth = canvasWidth;
	this->canvasHeight = canvasHeight;

	witch = { canvasHeight, 0.5f, 0.6f };
	skyLayer = { LoadTexture("assets/textures/background.png"), 0, canvasWidth, canvasHeight };
	cloudLayer = { LoadTexture("assets/textures/clouds.png"), 2, canvasWidth, canvasHeight };
	trees1Layer = { LoadTexture("assets/textures/trees1.png"), 25, canvasWidth, canvasHeight, 72 };
	trees2Layer = { LoadTexture("assets/textures/trees2.png"), 50, canvasWidth, canvasHeight, 48 };
	bushLayer = { LoadTexture("assets/textures/bush.png"), 100, canvasWidth, canvasHeight, 26 };
	groundLayer = { LoadTexture("assets/textures/ground.png"), 100, canvasWidth, canvasHeight };

	obstacleTexture = LoadTexture("assets/textures/obstacle.png");

	obstacle = { obstacleTexture, canvasWidth, canvasWidth, canvasHeight, 0.8f, 1.0f };
	obstacle2 = { obstacleTexture, canvasWidth + canvasWidth / 2, canvasWidth, canvasHeight, 0.8f, 1.0f };
}

int PlayState::calcNextObstacle(Obstacle* obstacles[], float witchPosition)
{
	float nextObstaclePosition{ 9999 };
	int nextObstacleIndex{ 0 };

	for (int i = 0; i < 2; i++)
	{
		if (obstacles[i]->getPositionX() < nextObstaclePosition)
		{
			if (obstacles[i]->getPositionX() > witchPosition)
			{
				nextObstaclePosition = obstacles[i]->getPositionX();
				nextObstacleIndex = i;
			}
		}
	}

	return nextObstacleIndex;
}

void PlayState::update(float deltaTime)
{
	collided = false;

	witch.update(deltaTime);

	for (auto layer : backgroundLayers)
	{
		layer->update(deltaTime);
	}

	for (auto obs : obstacles)
	{
		obs->update(deltaTime);
	}

	if (obstacles[nextObstacleIndex]->getPositionX() <= witch.getPositionX())
	{
		score++;

		if (score > maxScore) maxScore = score;

		nextObstacleIndex = calcNextObstacle(obstacles, witch.getPositionX());
	}

	for (auto obs : obstacles)
	{
		if (CheckCollisionRecs(witch.getCollisionRectangle(), obs->getCollisionRectangleTopObstacle()))
		{
			collided = true;
			break;
		}
		else if (CheckCollisionRecs(witch.getCollisionRectangle(), obs->getCollisionRectangleBottomObstacle()))
		{
			collided = true;
			break;
		}
	}

	if (collided)
	{
		gameStateManager.setGameState(std::make_unique<PlayState>(canvasWidth, canvasHeight, gameStateManager));
	}
}

void PlayState::render(float deltaTime)
{
	for (auto layer : backgroundLayers)
	{
		layer->render();
	}

	witch.render(deltaTime);

	for (auto obs : obstacles)
	{
		obs->render();
	}

	DrawText(TextFormat("Score: %i", score), 5, 5, 10, BLACK);
	//DrawText(TextFormat("Max Score: %i", maxScore), 5, 20, 1, BLACK);

	DrawText(TextFormat("%i FPS", GetFPS()), 5, canvasHeight - 10, 10, GREEN);
}

void PlayState::unloadAssets()
{
	witch.unloadAssets();

	for (auto layer : backgroundLayers)
	{
		layer->unloadAssets();
	}

	UnloadTexture(obstacleTexture);
}