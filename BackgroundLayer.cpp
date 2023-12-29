#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer(Texture texture, int scrollSpeed)
{
	this->texture = texture;
	this->scrollSpeed = scrollSpeed;
}

void BackgroundLayer::update(float deltaTime)
{
	position.x -= scrollSpeed * deltaTime;
	if (position.x <= -texture.width)
		position.x = 0;
}

void BackgroundLayer::render()
{
	DrawTexture(texture, position.x, 0, WHITE);
	DrawTexture(texture, position.x + texture.width, 0, WHITE);
}

void BackgroundLayer::unloadAssets()
{
	UnloadTexture(texture);
}