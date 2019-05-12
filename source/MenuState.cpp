#include "MenuState.h"
#include <StateManager.h>
#include <GameState.h>

MenuState::MenuState()
{
	// 312, 504, 

	menuBatch = new NHTV::SpriteBatch("../resources/images/MenuSheet.png");

	characters.m_Origin = { 0.5f, 0.5f };
	characters.m_Position = { 1280 / 2, 720 / 2 };
	characters.m_Size = { 1260, 504 };
	characters.m_MaxUV = { 1260.0f / 1576.0f, 1 };

	selection.m_Origin = { 0, 0.5f };
	selection.m_Position = { 10, 720 / 2 };
	selection.m_Size = { 312, 504 };
	selection.m_MinUV = { 1264.0f / 1576.0f, 0 };
	selection.m_Color.w = .3f;

	menuBatch->AddSprite(characters);
	menuBatch->AddSprite(selection);
}

MenuState::~MenuState()
{
	
}

void MenuState::Update(float deltaTime)
{
	left = application->IsKeyDown(NHTV::A);
	right = application->IsKeyDown(NHTV::D);

	if (left && !prevLeft && selection.m_Position.x > 10)
		selection.m_Position.x -= 316;

	if (right && !prevRight && selection.m_Position.x < 316*3)
		selection.m_Position.x += 316;

	prevLeft = left;
	prevRight = right;

	if (application->IsKeyDown(NHTV::SPACE))
	{
		int character = std::floor(selection.m_Position.x / 316);

		switch (character)
		{
		case 0: GameState::SetPlayableCharacter(Player::Character::Warrior); break;
		case 1: GameState::SetPlayableCharacter(Player::Character::Valkyrie); break;
		case 2: GameState::SetPlayableCharacter(Player::Character::Elf); break;
		case 3: GameState::SetPlayableCharacter(Player::Character::Wizard); break;
		}

		StateManager::ChangeState(StateManager::GameStates::Game);
	}
}

void MenuState::Draw()
{
	menuBatch->GetSprite(1) = selection;

	menuBatch->Draw();
}
