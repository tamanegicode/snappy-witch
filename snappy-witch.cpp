#include "raylib.h"
#include "TitleScreenState.h"
#include "GameStateManager.h"

const int canvasWidth{ 320 };
const int canvasHeight{ 180 };

int windowWidth{};
int windowHeight{};

Music backgroundMusic{};
RenderTexture renderTexture{};
GameStateManager gameStateManager;

void UpdateDrawFrame();

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT);

	InitWindow(0, 0, "Snappy Witch");
	InitAudioDevice();
	ToggleBorderlessWindowed();

	windowWidth = GetMonitorWidth(GetCurrentMonitor());
	windowHeight = GetMonitorHeight(GetCurrentMonitor());

	int framerateScale = GetMonitorRefreshRate(GetCurrentMonitor()) / 60;

	int targetFramerate{ 60 * framerateScale };

	SetTargetFPS(targetFramerate);	

	renderTexture = LoadRenderTexture(canvasWidth, canvasHeight);	

	int maxScore{ 0 };

	backgroundMusic = LoadMusicStream("assets/sounds/bgm.mp3");
	backgroundMusic.looping = true;
	SetMusicVolume(backgroundMusic, 0.6f);

	PlayMusicStream(backgroundMusic);

	gameStateManager.setGameState(std::make_unique<TitleScreenState>(canvasWidth, canvasHeight, gameStateManager, maxScore));

	while (WindowShouldClose() != true)
	{
		UpdateDrawFrame();
	}

	gameStateManager.cleanStack();

	UnloadRenderTexture(renderTexture);
	UnloadMusicStream(backgroundMusic);

	CloseAudioDevice();
	CloseWindow();
}

void UpdateDrawFrame()
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