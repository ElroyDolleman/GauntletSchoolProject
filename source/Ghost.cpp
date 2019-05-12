#include "Ghost.h"

Ghost::Ghost(Player& player)
	: Enemy(player)
{
	this->speed = 110;
	this->points = 20;

	this->animation = Animation(540, 608, { 64, 64 }, { 4, 4 }, { 0, 0 }, 24, .2f, 3);
	this->animation.SetAnimation(0, 2);
}

void Ghost::Update(float deltaTime)
{
	MoveTowards(GetPlayer().position, deltaTime);

	Enemy::Update(deltaTime);
}

void Ghost::Attacked(float power)
{
	Enemy::Attacked(power);
	sprite.m_Color.w = health / (GetMaxHealth() + .4f) + .4f;
}

void Ghost::HitPlayer()
{
	Enemy::HitPlayer();
	health = 0;
	points = 0;
}
