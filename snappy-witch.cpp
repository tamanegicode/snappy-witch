#include "raylib.h"
#include "Witch.h"
#include "BackgroundLayer.h"
#include "Obstacle.h"

int calcNextObstacle(Obstacle* obstacles[], float witchPosition)
{
	float nextObstaclePosition{ 9999 };
	int nextObstacleIndex{ 0 };

	for (int i = 0; i < 2; i++)
	{
		if (obstacles[i]->getPositionX() < nextObstaclePosition)
		{
			if (obstacles[i]->getPositionX() > witchPosition)
			{
				nextObstaclePosition = obstacles[i]->getPositionX();
				nextObstacleIndex = i;
			}
		}
	}

	return nextObstacleIndex;
}

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

	int nextObstacleIndex{ calcNextObstacle(obstacles, witch.getPositionX()) };

	int score{ 0 };
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

		if (obstacles[nextObstacleIndex]->getPositionX() <= witch.getPositionX())
		{
			score++;

			nextObstacleIndex = calcNextObstacle(obstacles, witch.getPositionX());
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

		if (collided)
		{
			score = 0;
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

		DrawText(TextFormat("Score: %i", score), 5 , 5, 10, BLACK);

		DrawText(TextFormat("%i FPS", GetFPS()), 5, canvasHeight - 10, 10, GREEN);

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