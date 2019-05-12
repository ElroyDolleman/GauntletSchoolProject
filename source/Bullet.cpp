#define _USE_MATH_DEFINES

#include "Bullet.h"
#include <cmath>

Bullet::Bullet(float x, float y, float direction, float speed)
	: speed(speed)
{
	position.x = x;
	position.y = y;

	sprite.m_Size = { 64, 64 };
	sprite.m_Origin = { 0.5f, 0.5f };

	SetDirection(direction);
}

void Bullet::Update(float deltaTime)
{
	if (sprite.m_Alive)
		MoveInDirection(direction, speed * deltaTime);
}

void Bullet::SetActive(bool isActive) {
	sprite.m_Alive = isActive;
}
bool Bullet::IsActive() const {
	return sprite.m_Alive;
}

void Bullet::SetDirection(float direction, bool spriteRotate)
{
	this->direction = direction * (M_PI / 180.0);

	if (spriteRotate)
		sprite.m_Rotation = this->direction;
}

float Bullet::GetDirection()
{
	return direction * (180 / M_PI);
}
