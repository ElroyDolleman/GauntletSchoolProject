#pragma once

#include <Enemy.h>

class Ghost : public Enemy
{
public:

	Ghost(Player& player);

	void Update(float deltaTime);
	void Attacked(float power);
	void HitPlayer();

private:


};