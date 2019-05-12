#include "State.h"

State::State()
{
	application = &NHTV::Application::GetInstance();
}

State::~State()
{
}

void State::Update(float deltaTime)
{
}

void State::Draw()
{
}
