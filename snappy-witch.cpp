#include "raylib.h"
#include "PlayState.h"

int main()
{
	const int canvasWidth{ 320 };
	const int canvasHeight{ 180 };

	const int windowWidth{ canvasWidth * 4 };
	const int windowHeight{ canvasHeight * 4 };

	InitWindow(windowWidth, windowHeight, "Snappy Witch");
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	RenderTexture renderTexture{ LoadRenderTexture(canvasWidth, canvasHeight) };

	PlayState playState{ canvasWidth, canvasHeight };

	while (WindowShouldClose() != true)
	{
		const float deltaTime{ GetFrameTime() };

		playState.update(deltaTime);

		BeginTextureMode(renderTexture);
		ClearBackground(GRAY);

		playState.render(deltaTime);

		EndTextureMode();

		BeginDrawing();
		DrawTexturePro(renderTexture.texture, Rectangle{ 0, 0, canvasWidth, -canvasHeight }, Rectangle{ 0, 0, windowWidth, windowHeight }, Vector2{ 0, 0 }, 0.0f, WHITE);
		EndDrawing();
	}

	playState.unloadAssets();

	UnloadRenderTexture(renderTexture);

	CloseWindow();
}