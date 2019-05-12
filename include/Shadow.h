#pragma once

#include <Enemy.h>

class Shadow : public Enemy
{
public:

	Shadow(Player& player);

	void Update(float deltaTime);
	void Attacked(float power);
	void HitPlayer();

private:

	bool chasing;
	float range;
	float damage;

	bool gotHit;
	bool flicker;
	float flickerTimer;
	float flickerInterval;
};