#include "GameStateManager.h"

GameStateManager::GameStateManager()
{
}

void GameStateManager::setGameState(std::unique_ptr <GameState> newState)
{
	if (!gameStates.empty())
	{
		unloadAssets();
		gameStates.pop();
	}
	gameStates.push(std::move(newState));
}

void GameStateManager::update(float deltaTime)
{
	gameStates.top()->update(deltaTime);
}

void GameStateManager::render(float deltaTime)
{
	gameStates.top()->render(deltaTime);
}

void GameStateManager::unloadAssets()
{
	gameStates.top()->unloadAssets();
}