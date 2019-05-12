#pragma once

#include <Application.h>

class State
{
public:

	State();
	virtual ~State();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:

	NHTV::Application* application;
};