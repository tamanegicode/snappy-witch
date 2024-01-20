#include "PlayState.h"

PlayState::PlayState(int cW, int cH, GameStateManager& gSM) : canvasWidth(cW), canvasHeight(cH), gameStateManager(gSM)
{
}

int PlayState::calcNextObstacle(std::unique_ptr <Obstacle> obstacles[], float witchPosition)
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

	for (auto &layer : backgroundLayers)
	{
		layer->update(deltaTime);
	}

	for (auto &obs : obstacles)
	{
		obs->update(deltaTime);
	}

	if (obstacles[nextObstacleIndex]->getPositionX() <= witch.getPositionX())
	{
		score++;

		if (score > maxScore) maxScore = score;

		nextObstacleIndex = calcNextObstacle(obstacles, witch.getPositionX());
	}

	for (auto &obs : obstacles)
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
	for (auto &layer : backgroundLayers)
	{
		layer->render();
	}

	witch.render(deltaTime);

	for (auto &obs : obstacles)
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

	for (auto &layer : backgroundLayers)
	{
		layer->unloadAssets();
	}

	UnloadTexture(obstacleTexture);
}