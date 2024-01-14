#pragma once
#include "GameState.h"
#include <stack>

class GameStateManager
{
public:
	GameStateManager(GameState& newState);
	void setGameState(GameState& newState);
	void update(float deltaTime);
	void render(float deltaTime);
	void unloadAssets();
private:
	std::stack<GameState*> gameStates{};
};