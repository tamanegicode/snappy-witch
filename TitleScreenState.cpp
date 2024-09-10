#include "TitleScreenState.h"
#include "PlayState.h"

TitleScreenState::TitleScreenState(int canvasWidth, int canvasHeight, GameStateManager& gameStateManager, int& maxScore)
	: m_CanvasWidth(canvasWidth), m_CanvasHeight(canvasHeight), m_GameStateManager(gameStateManager), m_MaxScore(maxScore)
{
}

void TitleScreenState::update(float deltaTime)
{
	Vector2 scaledMousePosition{ static_cast<float>(GetMouseX() * m_CanvasWidth / GetScreenWidth()), static_cast<float>(GetMouseY() * m_CanvasHeight / GetScreenHeight()) };

	isMouseOverPlayButton = CheckCollisionPointRec(scaledMousePosition, playButtonCollisionRectangle);

	if (isMouseOverPlayButton && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		fadeIn = false;
	}

	clouds.update(deltaTime);

	if (!fadeIn)
	{
		if(fadeColor.a >= 255)
			m_GameStateManager.setGameState(std::make_unique<PlayState>(m_CanvasWidth, m_CanvasHeight, m_GameStateManager, m_MaxScore));
	}
}

void TitleScreenState::render(float deltaTime)
{
	DrawTexture(sky, 0, 0, WHITE);
	clouds.render();
	DrawTexture(trees1, 0, m_CanvasHeight - trees1.height, WHITE);
	DrawTexture(trees2, 0, m_CanvasHeight - trees2.height, WHITE);	

	witchAnimationTime += deltaTime;

	if (witchAnimationTime > witchFrameTime)
	{
		witchFrameToDraw == witchFrameNumber - 1 ? witchFrameToDraw = 0 : witchFrameToDraw += 1;
		witchAnimationTime = 0;
	}

	batAnimationTime += deltaTime;

	if (batAnimationTime > batFrameTime)
	{
		batFrameToDraw == batFrameNumber - 1 ? batFrameToDraw = 0 : batFrameToDraw += 1;
		batAnimationTime = 0;
	}

	DrawTexturePro(witch,
		Rectangle{ static_cast<float>(witch.width / witchFrameNumber) * witchFrameToDraw, 0, static_cast<float>(witch.width / witchFrameNumber), static_cast<float>(witch.height) },
		Rectangle{ static_cast<float>(m_CanvasWidth / 2 - (witch.width / witchFrameNumber) / 2), 15, static_cast<float>(witch.width / witchFrameNumber), static_cast<float>(witch.height)},
		Vector2{ 0, 0 },
		0.0f,
		WHITE);

	DrawTexturePro(bat,
		Rectangle{ static_cast<float>(bat.width / batFrameNumber) * batFrameToDraw, 0, static_cast<float>(bat.width / batFrameNumber), static_cast<float>(bat.height) },
		Rectangle{ static_cast<float>(m_CanvasWidth / 2 + 15), 35, static_cast<float>(bat.width / batFrameNumber), static_cast<float>(bat.height) },
		Vector2{ 0, 0 },
		0.0f,
		WHITE);

	DrawTexture(thorns, 0, 0, WHITE);

	DrawTexture(logo, m_CanvasWidth / 2 - logo.width / 2, 90, WHITE);

	if (isMouseOverPlayButton)
	{
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			DrawTexture(playButtonPressed, playButtonPosition.x, playButtonPosition.y, WHITE);
		else
			DrawTexture(playButtonHover, playButtonPosition.x, playButtonPosition.y, WHITE);
	}
	else
	{
		DrawTexture(playButtonDefault, playButtonPosition.x, playButtonPosition.y, WHITE);
	}

	if (fadeColor.a > 0 && fadeIn)
	{
		if (fadeColor.a - fadeSpeed * deltaTime < 0)
			fadeColor.a = 0;
		else
			fadeColor.a -= fadeSpeed * deltaTime;

		DrawRectangle(0, 0, m_CanvasWidth, m_CanvasHeight, fadeColor);
	}
	else if (fadeColor.a <= 255 && !fadeIn)
	{
		if (fadeColor.a + fadeSpeed * deltaTime > 255)
			fadeColor.a = 255;
		else
			fadeColor.a += fadeSpeed * deltaTime;

		DrawRectangle(0, 0, m_CanvasWidth, m_CanvasHeight, fadeColor);
	}
}

void TitleScreenState::unloadAssets()
{
	UnloadTexture(sky);
	clouds.unloadAssets();
	UnloadTexture(trees1);
	UnloadTexture(trees2);
	UnloadTexture(logo);
	UnloadTexture(witch);
	UnloadTexture(bat);
	UnloadTexture(thorns);
	UnloadTexture(playButtonDefault);
	UnloadTexture(playButtonHover);
	UnloadTexture(playButtonPressed);
}