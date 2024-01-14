#include "GameStateManager.h"

GameStateManager::GameStateManager(GameState &newState)
{
	gameStates.push(&newState);
}

void GameStateManager::setGameState(GameState &newState)
{
	gameStates.pop();
	gameStates.push(&newState);
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