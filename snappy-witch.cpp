#include "raylib.h"
#include "Witch.h"

int main()
{
	const int windowWidth{ 1280 };
	const int windowHeight{ 720 };

	InitWindow(windowWidth, windowHeight, "Snappy Witch");
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	Witch witch(windowHeight);

	while (WindowShouldClose() != true)
	{
		float deltaTime{ GetFrameTime() };

		witch.update(deltaTime);

		BeginDrawing();
		ClearBackground(GRAY);

		witch.render();

		EndDrawing();
	}

	witch.unloadAssets();
	CloseWindow();
}