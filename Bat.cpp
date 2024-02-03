#include "Bat.h"
#include "raymath.h"

Bat::Bat(Vector2 &witchPosition)
{
	m_WitchPosition = &witchPosition;
}

void Bat::update(float deltaTime)
{

	direction = Vector2Subtract(Vector2Add(*m_WitchPosition, offset), position);

	if (Vector2Length(direction) <= 5.0f)
		return;

	direction = Vector2Normalize(direction);

	direction = Vector2Scale(direction, speed * deltaTime);

	position = Vector2Add(position, direction);
}

void Bat::render(float deltaTime)
{
	animationTime += deltaTime;

	if (animationTime > frameTime)
	{
		frameToDraw == frameNumber - 1 ? frameToDraw = 0 : frameToDraw += 1;
		animationTime = 0;
	}

	DrawTexturePro(texture,
		Rectangle{ static_cast<float>(texture.width / frameNumber) * frameToDraw, 0, static_cast<float>(texture.width / frameNumber), static_cast<float>(texture.height) },
		Rectangle{ position.x, position.y, static_cast<float>(texture.width / frameNumber), static_cast<float>(texture.height) },
		Vector2{ 0, 0 },
		0.0f,
		WHITE);
}

void Bat::unloadAssets()
{
	UnloadTexture(texture);

	delete m_WitchPosition;
}