#include "raylib.h"
#include "Witch.h"
#include "BackgroundLayer.h"

int main()
{
	const int windowWidth{ 1280 };
	const int windowHeight{ 720 };

	InitWindow(windowWidth, windowHeight, "Snappy Witch");
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	Witch witch(windowHeight);

	BackgroundLayer backLayer(LoadTexture("assets/textures/backlayer.png"), 100);
	BackgroundLayer midLayer(LoadTexture("assets/textures/midlayer.png"), 200);
	BackgroundLayer frontLayer(LoadTexture("assets/textures/frontlayer.png"), 400);

	BackgroundLayer* backgroundLayers[]{
		&backLayer,
		&midLayer,
		&frontLayer
	};

	while (WindowShouldClose() != true)
	{
		float deltaTime{ GetFrameTime() };

		witch.update(deltaTime);

		for (auto layer : backgroundLayers)
		{
			layer->update(deltaTime);
		}

		BeginDrawing();
		ClearBackground(GRAY);

		for (auto layer : backgroundLayers)
		{
			layer->render();
		}

		witch.render();

		DrawFPS(10, 10);

		EndDrawing();
	}

	witch.unloadAssets();
	backLayer.unloadAssets();
	midLayer.unloadAssets();
	frontLayer.unloadAssets();

	CloseWindow();
}