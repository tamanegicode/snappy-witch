#include "raylib.h"
#include "TitleScreenState.h"
#include "GameStateManager.h"

int main()
{
	const int canvasWidth{ 320 };
	const int canvasHeight{ 180 };

	SetConfigFlags(FLAG_VSYNC_HINT);

	InitWindow(0, 0, "Snappy Witch");
	InitAudioDevice();
	ToggleBorderlessWindowed();

	const int windowWidth{ GetMonitorWidth(GetCurrentMonitor()) };
	const int windowHeight{ GetMonitorHeight(GetCurrentMonitor()) };

	int framerateScale = GetMonitorRefreshRate(GetCurrentMonitor()) / 60;

	int targetFramerate{ 60 * framerateScale };

	SetTargetFPS(targetFramerate);	

	RenderTexture renderTexture{ LoadRenderTexture(canvasWidth, canvasHeight) };

	GameStateManager gameStateManager;

	int maxScore{ 0 };

	Music backgroundMusic = LoadMusicStream("assets/sounds/bgm.mp3");
	backgroundMusic.looping = true;

	PlayMusicStream(backgroundMusic);

	gameStateManager.setGameState(std::make_unique<TitleScreenState>(canvasWidth, canvasHeight, gameStateManager, maxScore));

	while (WindowShouldClose() != true)
	{
		const float deltaTime{ GetFrameTime() };

		UpdateMusicStream(backgroundMusic);

		gameStateManager.update(deltaTime);

		BeginTextureMode(renderTexture);
		ClearBackground(GRAY);

		gameStateManager.render(deltaTime);

		EndTextureMode();

		BeginDrawing();
		DrawTexturePro(renderTexture.texture, Rectangle{ 0, 0, canvasWidth, -canvasHeight }, Rectangle{ 0, 0, static_cast<float>(windowWidth), static_cast<float>(windowHeight) }, Vector2{ 0, 0 }, 0.0f, WHITE);
		EndDrawing();
	}

	gameStateManager.cleanStack();

	UnloadRenderTexture(renderTexture);
	UnloadMusicStream(backgroundMusic);

	CloseWindow();
}