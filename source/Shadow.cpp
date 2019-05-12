#include "Shadow.h"

Shadow::Shadow(Player& player)
	: Enemy(player)
{
	this->speed = 140;
	this->points = 100;
	this->range = 280;
	this->resistance = 10;
	this->damage = 0;

	this->animation = Animation(540, 608, { 64, 64 }, { 4, 4 }, { 204, 0 }, 24, .2f, 3);
	this->animation.SetAnimation(0, 2);

	sprite.m_MinUV = animation.GetUVCoords().xy;
	sprite.m_MaxUV = animation.GetUVCoords().zw;

	gotHit = false;
	flicker = false;
	flickerTimer = 0;
	flickerInterval = .2f;

	chasing = false;
}

void Shadow::Update(float deltaTime)
{
	int health = GetPlayer().GetHealth();

	Enemy::Update(deltaTime);

	if (chasing)
	{
		if (!GetPlayer().GetHitbox().Intersects(this->GetHitbox()))
			MoveTowards(GetPlayer().position, deltaTime);
		else
			direction = { 0, 0 };
	}
	else if (DistanceTo(GetPlayer().position) < range)
		chasing = true;

	// Flickering effect
	if (gotHit)
	{
		if (flicker)
			sprite.m_Color.x = 255;
		else
			sprite.m_Color.x = 0;

		flicker = !flicker;

		flickerTimer += deltaTime;

		if (flickerTimer >= flickerInterval)
		{
			flickerTimer = 0;
			gotHit = false;
			sprite.m_Color.x = 0;
		}
	}
}

void Shadow::Attacked(float power)
{
	Enemy::Attacked(power);

	gotHit = true;
	chasing = true;
}

void Shadow::HitPlayer()
{
	damage += .2f;
	if (damage >= 1)
	{
		GetPlayer().LoseHealth(damage);
		damage = 0;
	}
}
