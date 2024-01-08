#include "raylib.h"
#include "Witch.h"
#include "BackgroundLayer.h"
#include "Obstacle.h"

int main()
{
	const int windowWidth{ 1280 };
	const int windowHeight{ 720 };

	InitWindow(windowWidth, windowHeight, "Snappy Witch");	
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	Witch witch(windowHeight, 0.6f);

	BackgroundLayer backLayer(LoadTexture("assets/textures/backlayer.png"), 100, windowWidth, windowHeight);
	BackgroundLayer midLayer(LoadTexture("assets/textures/midlayer.png"), 200, windowWidth, windowHeight);
	BackgroundLayer frontLayer(LoadTexture("assets/textures/frontlayer.png"), 300, windowWidth, windowHeight);
	BackgroundLayer groundLayer(LoadTexture("assets/textures/ground.png"), 400, windowWidth, windowHeight);
	BackgroundLayer bushLayer(LoadTexture("assets/textures/bush.png"), 400, windowWidth, windowHeight, 24);

	BackgroundLayer* backgroundLayers[]{
		&backLayer,
		&midLayer,
		&frontLayer,
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

		for (auto obs : obstacles)
		{
			if (CheckCollisionRecs(witch.getCollisionRectangle(), obs->getCollisionRectangleTopObstacle()))
			{
				collided = true;
			}
			else if (CheckCollisionRecs(witch.getCollisionRectangle(), obs->getCollisionRectangleBottomObstacle()))
			{
				collided = true;
			}
		}

		if (collided)
		{
			char hitText[] = "I'M HIT";
			int hitTextSize = 100;
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