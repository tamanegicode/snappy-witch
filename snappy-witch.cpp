#include "raylib.h"
#include "Witch.h"
#include "BackgroundLayer.h"
#include "Obstacle.h"

int main()
{
	const int canvasWidth{ 320 };
	const int canvasHeight{ 180 };

	const int windowWidth{ canvasWidth * 4 };
	const int windowHeight{ canvasHeight * 4 };

	InitWindow(windowWidth, windowHeight, "Snappy Witch");
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	RenderTexture renderTexture = LoadRenderTexture(canvasWidth, canvasHeight);

	Witch witch(canvasHeight, 0.6f);

	BackgroundLayer skyLayer(LoadTexture("assets/textures/background.png"), 0, canvasWidth, canvasHeight);
	BackgroundLayer cloudLayer(LoadTexture("assets/textures/clouds.png"), 2, canvasWidth, canvasHeight);
	BackgroundLayer trees1Layer(LoadTexture("assets/textures/trees1.png"), 25, canvasWidth, canvasHeight, 72);
	BackgroundLayer trees2Layer(LoadTexture("assets/textures/trees2.png"), 50, canvasWidth, canvasHeight, 48);
	BackgroundLayer bushLayer(LoadTexture("assets/textures/bush.png"), 100, canvasWidth, canvasHeight, 26);
	BackgroundLayer groundLayer(LoadTexture("assets/textures/ground.png"), 100, canvasWidth, canvasHeight);

	BackgroundLayer* backgroundLayers[]{
		&skyLayer,
		&cloudLayer,
		&trees1Layer,
		&trees2Layer,
		&bushLayer,
		&groundLayer
	};

	Texture obstacleTexture = LoadTexture("assets/textures/obstacle.png");

	Obstacle obstacle(obstacleTexture, canvasWidth, canvasWidth, canvasHeight);
	Obstacle obstacle2(obstacleTexture, canvasWidth + canvasWidth / 2, canvasWidth, canvasHeight);

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

		BeginTextureMode(renderTexture);
		ClearBackground(GRAY);

		for (auto layer : backgroundLayers)
		{
			layer->render();
		}

		witch.render(deltaTime);

		for (auto obs : obstacles)
		{
			obs->render();
		}

		if (collided)
		{
			char hitText[] = "I'M HIT";
			int hitTextSize = 50;
			int hitTextWidth = MeasureText(hitText, hitTextSize);

			DrawText(hitText, canvasWidth / 2 - hitTextWidth / 2, canvasHeight / 2, hitTextSize, BLACK);
		}

		DrawFPS(10, 10);

		EndTextureMode();

		BeginDrawing();
		DrawTexturePro(renderTexture.texture, Rectangle{ 0, 0, canvasWidth, -canvasHeight }, Rectangle{ 0, 0, windowWidth, windowHeight }, Vector2{ 0, 0 }, 0.0f, WHITE);
		EndDrawing();
	}

	witch.unloadAssets();

	for (auto layer : backgroundLayers)
	{
		layer->unloadAssets();
	}

	UnloadTexture(obstacleTexture);

	UnloadRenderTexture(renderTexture);

	CloseWindow();
}