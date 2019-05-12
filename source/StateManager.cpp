#include "StateManager.h"
#include "MenuState.h"
#include "GameState.h"

State* currentState = nullptr;

void StateManager::Launch()
{
	SetState();
}

void StateManager::Delete()
{
	delete currentState;
}

void StateManager::ChangeState(GameStates state)
{
	delete currentState;

	SetState(state);
}

void StateManager::Update(float deltaTime)
{
	currentState->Update(deltaTime);
}

void StateManager::Draw()
{
	currentState->Draw();
}

void StateManager::SetState(GameStates state)
{
	switch (state)
	{
	case StateManager::Menu:
		currentState = new MenuState();
		break;
	case StateManager::Game:
		currentState = new GameState();
		break;
	}
}
