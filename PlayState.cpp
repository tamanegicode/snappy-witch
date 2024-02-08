#include "PlayState.h"

PlayState::PlayState(int canvasWidth, int canvasHeight, GameStateManager& gameStateManager, int& maxScore)
	: m_CanvasWidth(canvasWidth), m_CanvasHeight(canvasHeight), m_GameStateManager(gameStateManager), m_MaxScore(maxScore)
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
	witch.update(deltaTime);

	if (witch.getDead())
	{
		countdownToReset -= deltaTime;
		if (countdownToReset <= 0)
			m_GameStateManager.setGameState(std::make_unique<PlayState>(m_CanvasWidth, m_CanvasHeight, m_GameStateManager, m_MaxScore));

		return;
	}

	bat.update(deltaTime);

	for (auto& layer : backgroundLayers)
	{
		layer->update(deltaTime);
	}

	for (auto& obs : obstacles)
	{
		obs->update(deltaTime);
	}

	if (obstacles[nextObstacleIndex]->getPositionX() + obstacles[nextObstacleIndex]->getCollisionRectangleBottomObstacle().width <= witch.getCollisionRectangle().x)
	{
		score++;

		if (score > m_MaxScore) m_MaxScore = score;

		nextObstacleIndex = calcNextObstacle(obstacles, witch.getPositionX());
	}

	for (auto& obs : obstacles)
	{
		if (CheckCollisionRecs(witch.getCollisionRectangle(), obs->getCollisionRectangleTopObstacle()))
		{
			witch.setDead();
			break;
		}
		else if (CheckCollisionRecs(witch.getCollisionRectangle(), obs->getCollisionRectangleBottomObstacle()))
		{
			witch.setDead();
			break;
		}
	}
}

void PlayState::render(float deltaTime)
{
	for (auto& layer : backgroundLayers)
	{
		layer->render();
	}

	witch.render(deltaTime);

	bat.render(deltaTime);

	for (auto& obs : obstacles)
	{
		obs->render();
	}

	DrawText(TextFormat("Score: %i", score), 5, 5, 10, BLACK);
	DrawText(TextFormat("Max Score: %i", m_MaxScore), 5, 20, 1, BLACK);

	//Uncomment to make current FPS visible for testing purposes
	//DrawText(TextFormat("%i FPS", GetFPS()), 5, m_CanvasHeight - 10, 10, GREEN);
}

void PlayState::unloadAssets()
{
	witch.unloadAssets();

	for (auto& layer : backgroundLayers)
	{
		layer->unloadAssets();
	}

	UnloadTexture(obstacleTexture);
}