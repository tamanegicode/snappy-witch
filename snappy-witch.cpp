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

	Witch witch(windowHeight);

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

	while (WindowShouldClose() != true)
	{
		const float deltaTime{ GetFrameTime() };

		witch.update(deltaTime);

		for (auto layer : backgroundLayers)
		{
			layer->update(deltaTime);
		}

		obstacle.update(deltaTime);
		obstacle2.update(deltaTime);

		BeginDrawing();
		ClearBackground(GRAY);

		for (auto layer : backgroundLayers)
		{
			layer->render();
		}

		witch.render();

		obstacle.render();
		obstacle2.render();

		DrawFPS(10, 10);

		EndDrawing();
	}

	witch.unloadAssets();

	for (auto layer : backgroundLayers)
	{
		layer->unloadAssets();
	}

	obstacle.unloadAssets();
	obstacle2.unloadAssets();

	CloseWindow();
}