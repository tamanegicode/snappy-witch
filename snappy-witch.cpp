#include "raylib.h"
#include "Witch.h"
#include "BackgroundLayer.h"
#include "Obstacle.h"

int main()
{
	const int windowWidth{ 320 };
	const int windowHeight{ 180 };

	InitWindow(windowWidth, windowHeight, "Snappy Witch");
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	Witch witch(windowHeight, 0.6f);

	BackgroundLayer skyLayer(LoadTexture("assets/textures/background.png"), 0, windowWidth, windowHeight);
	BackgroundLayer cloudLayer(LoadTexture("assets/textures/clouds.png"), 2, windowWidth, windowHeight);
	BackgroundLayer trees1Layer(LoadTexture("assets/textures/trees1.png"), 25, windowWidth, windowHeight, 72);
	BackgroundLayer trees2Layer(LoadTexture("assets/textures/trees2.png"), 50, windowWidth, windowHeight, 48);
	BackgroundLayer bushLayer(LoadTexture("assets/textures/bush.png"), 100, windowWidth, windowHeight, 26);
	BackgroundLayer groundLayer(LoadTexture("assets/textures/ground.png"), 100, windowWidth, windowHeight);

	BackgroundLayer* backgroundLayers[]{
		&skyLayer,
		&cloudLayer,
		&trees1Layer,
		&trees2Layer,
		&bushLayer,
		&groundLayer
	};

	Obstacle obstacle(LoadTexture("assets/textures/obstacle.png"), windowWidth, windowWidth);
	Obstacle obstacle2(LoadTexture("assets/textures/obstacle.png"), windowWidth + windowWidth / 2, windowWidth);

	Obstacle* obstacles[]{
		&obstacle,
		&obstacle2
	};

	bool collided{};

	while (WindowShouldClose() != true)
	{
		const float deltaTime{ GetFrameTime() };

		collided = false;

		witch.update(deltaTime);

		for (auto layer : backgroundLayers)
		{
			layer->update(deltaTime);
		}

		for (auto obs : obstacles)
		{
			obs->update(deltaTime);
		}

		for (auto obs : obstacles)
		{
			if (CheckCollisionRecs(witch.getCollisionRectangle(), obs->getCollisionRectangleTopObstacle()))
			{
				collided = true;
				break;
			}
			else if (CheckCollisionRecs(witch.getCollisionRectangle(), obs->getCollisionRectangleBottomObstacle()))
			{
				collided = true;
				break;
			}
		}

		BeginDrawing();
		ClearBackground(GRAY);

		for (auto layer : backgroundLayers)
		{
			layer->render();
		}

		witch.render();

		for (auto obs : obstacles)
		{
			obs->render();
		}

		if (collided)
		{
			char hitText[] = "I'M HIT";
			int hitTextSize = 50;
			int hitTextWidth = MeasureText(hitText, hitTextSize);

			DrawText(hitText, windowWidth / 2 - hitTextWidth / 2, windowHeight / 2, hitTextSize, BLACK);
		}

		DrawFPS(10, 10);

		EndDrawing();
	}

	witch.unloadAssets();

	for (auto layer : backgroundLayers)
	{
		layer->unloadAssets();
	}

	for (auto obs : obstacles)
	{
		obs->unloadAssets();
	}

	CloseWindow();
}