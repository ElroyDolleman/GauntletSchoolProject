#include "GameUI.h"
#include <string>

GameUI::GameUI()
{
	background.m_Size = { 320, 720 };
	background.m_MinUV = { 1 - 1 / 64, 0 };
	background.m_MaxUV = { 1, 1 / 64 };
	background.m_Position = GetPosition();
	background.m_Origin = { 0, 0 };

	key.m_Size = { 16, 32 };
	key.m_MinUV = { 0, .5f };
	key.m_MaxUV = { .25f, 1 };
	key.m_Origin = { 0, 0 };

	score = 0;
	keys = 0;
}

GameUI::~GameUI()
{

}

void GameUI::Draw(NHTV::SpriteBatch &spriteBatch)
{
	std::vector<NHTV::SpriteBatch::Sprite> sprites;
	sprites.push_back(background);

	for (int i = 0; i < std::fmin(10, keys); i++)
	{
		key.m_Position = { GetPosition().x + 32 + (26 * i), 300 };
		sprites.push_back(key);
	}

	spriteBatch.Draw(sprites);
}

glm::vec2 GameUI::GetPosition() {
	return { 960, 0 };
}
glm::vec2 GameUI::GetCenterPosition() {
	return { 960 + (1280 - 960) / 2, 720 / 2 };
}

std::string GameUI::GetHealthText(int health) {
	return "health: " + std::to_string(health);
}
std::string GameUI::GetScoreText() {
	return "score:  " + std::to_string(score);
}
