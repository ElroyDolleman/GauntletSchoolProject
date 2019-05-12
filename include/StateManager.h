#pragma once

#include "State.h"

class StateManager
{
public: 
	enum GameStates { Menu, Game };

	static void Launch();
	static void ChangeState(GameStates state = GameStates::Menu);
	static void Update(float deltaTime);
	static void Draw();
	static void Delete();

private:

	static void SetState(GameStates state = GameStates::Menu);
};