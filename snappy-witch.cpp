#include "raylib.h"

int main()
{
	const int windowWidth{ 1280 };
	const int windowHeight{ 720 };

	InitWindow(windowWidth, windowHeight, "Snappy Witch");
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	while (WindowShouldClose() != true)
	{
		BeginDrawing();
		ClearBackground(WHITE);
		EndDrawing();
	}

	CloseWindow();
}