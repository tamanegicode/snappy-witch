#pragma once

class GameState
{
public:
	GameState();
	virtual void update(float deltaTime) =0;
	virtual void render(float deltaTime) =0;
	virtual void unloadAssets() =0;
private:
};