#pragma once
#include <SpriteBatch.h>

class GameUI
{
public:

	GameUI();
	~GameUI();

	void Draw(NHTV::SpriteBatch& spriteBatch);

	NHTV::SpriteBatch::Sprite background;
	NHTV::SpriteBatch::Sprite key;

	glm::vec2 GetPosition();
	glm::vec2 GetCenterPosition();
	std::string GetHealthText(int health);
	std::string GetScoreText();

	int score;
	int keys;

private:


};