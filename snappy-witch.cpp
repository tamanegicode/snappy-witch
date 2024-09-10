#include "raylib.h"
#include "TitleScreenState.h"
#include "GameStateManager.h"

//Uncomment if building for Web. Leave as is if building for PC.
//#define PLATFORM_WEB

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

const int canvasWidth{ 320 };
const int canvasHeight{ 180 };
float canvasScale{ 1.0f };
Vector2 canvasPosition{ 0,0 };

int windowWidth{ canvasWidth };
int windowHeight{ canvasHeight };

int lastWindowWidth{ windowWidth };
int lastWindowHeight{ windowHeight };

Music backgroundMusic{};
RenderTexture renderTexture{};
GameStateManager gameStateManager;

void UpdateDrawFrame();
void ResizeToFitWindow();

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(windowWidth, windowHeight, "Snappy Witch");
	SetWindowMinSize(canvasWidth, canvasHeight);
	InitAudioDevice();
	ToggleBorderlessWindowed();

#ifndef PLATFORM_WEB
	int framerateScale = GetMonitorRefreshRate(GetCurrentMonitor()) / 60;

	int targetFramerate{ 60 * framerateScale };

	SetTargetFPS(targetFramerate);
#endif

	renderTexture = LoadRenderTexture(canvasWidth, canvasHeight);	

	int maxScore{ 0 };

	backgroundMusic = LoadMusicStream("assets/sounds/bgm.mp3");
	backgroundMusic.looping = true;
	SetMusicVolume(backgroundMusic, 0.6f);

	PlayMusicStream(backgroundMusic);

	gameStateManager.setGameState(std::make_unique<TitleScreenState>(canvasWidth, canvasHeight, gameStateManager, maxScore));

	ResizeToFitWindow();

#ifdef PLATFORM_WEB
	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
	while (WindowShouldClose() != true)
	{
		UpdateDrawFrame();
	}
#endif

	gameStateManager.cleanStack();

	UnloadRenderTexture(renderTexture);
	UnloadMusicStream(backgroundMusic);

	CloseAudioDevice();
	CloseWindow();
}

void UpdateDrawFrame()
{
	const float deltaTime{ GetFrameTime() };

#ifdef PLATFORM_WEB
	if (GetScreenWidth() != lastWindowWidth || GetScreenHeight() != lastWindowHeight)
	{
		ResizeToFitWindow();
	}
#endif	

	UpdateMusicStream(backgroundMusic);

	gameStateManager.update(deltaTime);

	BeginTextureMode(renderTexture);
	ClearBackground(GRAY);

	gameStateManager.render(deltaTime);

	EndTextureMode();

	BeginDrawing();
	DrawRectangle(0, 0, windowWidth, windowHeight, BLACK);
	DrawTexturePro(renderTexture.texture, 
		Rectangle{ 0, 0, canvasWidth, -canvasHeight }, 
		Rectangle{ canvasPosition.x, canvasPosition.y, static_cast<float>(canvasWidth * canvasScale), static_cast<float>(canvasHeight * canvasScale) },
		Vector2{ 0, 0 }, 0.0f, WHITE);
	EndDrawing();
}

void ResizeToFitWindow()
{
	windowWidth = GetScreenWidth();
	windowHeight = GetScreenHeight();

	lastWindowWidth = windowWidth;
	lastWindowHeight = windowHeight;

	canvasScale = fminf((float)windowWidth / canvasWidth, (float)windowHeight / canvasHeight);

	canvasPosition.x = (windowWidth - (canvasWidth * canvasScale)) * 0.5f;
	canvasPosition.y = (windowHeight - (canvasHeight * canvasScale)) * 0.5f;
}