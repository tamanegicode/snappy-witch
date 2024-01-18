#pragma once
#include "GameState.h"
#include <stack>
#include <memory>

class GameStateManager
{
public:
	GameStateManager();
	void setGameState(std::unique_ptr <GameState> newState);
	void update(float deltaTime);
	void render(float deltaTime);
	void unloadAssets();
private:
	std::stack<std::unique_ptr<GameState>> gameStates{};
};