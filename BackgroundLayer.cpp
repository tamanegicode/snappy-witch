#include "BackgroundLayer.h"
#include <cmath>

BackgroundLayer::BackgroundLayer(std::string texturePath, int scrollSpeed, int canvasWidth, int canvasHeight, int offset) : m_TexturePath(texturePath)
{
	this->scrollSpeed = scrollSpeed;
	this->canvasWidth = canvasWidth;
	this->canvasHeight = canvasHeight;
	this->offset = offset;

	numberOfSprites = scrollSpeed == 0 ? 1 : std::ceil((static_cast<float>(canvasWidth) / static_cast<float>(texture.width)));
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
		DrawTexture(texture, static_cast<int>(position.x) + texture.width * i, canvasHeight - offset - texture.height, WHITE);
	}
}

void BackgroundLayer::unloadAssets()
{
	UnloadTexture(texture);
}