#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer(Texture texture, int scrollSpeed, int windowWidth, int windowHeight, int offset)
{
	this->texture = texture;
	this->scrollSpeed = scrollSpeed;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->offset = offset;

	numberOfSprites = windowWidth / texture.width;
}

void BackgroundLayer::update(float deltaTime)
{
	position.x -= scrollSpeed * deltaTime;
	if (static_cast<int>(position.x) <= -texture.width)
		position.x = 0;
}

void BackgroundLayer::render()
{
	for (size_t i = 0; i <= numberOfSprites; i++)
	{
		DrawTexture(texture, static_cast<int>(position.x) + texture.width * i, windowHeight - offset - texture.height, WHITE);
	}
}

void BackgroundLayer::unloadAssets()
{
	UnloadTexture(texture);
}