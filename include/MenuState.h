#pragma once

#include <State.h>
#include <SpriteBatch.h>

class MenuState : public State
{
public:

	MenuState();
	~MenuState();

	void Update(float deltaTime);
	void Draw();

private:

	NHTV::SpriteBatch* menuBatch;
	NHTV::SpriteBatch::Sprite characters;
	NHTV::SpriteBatch::Sprite selection;

	bool left, prevLeft;
	bool right, prevRight;
};