#pragma once

#include "Entity.h"

class Bullet : public Entity
{
public:

	Bullet(float x, float y, float direction, float speed);

	void Update(float deltaTime);

	void SetActive(bool isActive);
	bool IsActive() const;

	void SetDirection(float direction, bool spriteRotate = true);
	float GetDirection();

private:

	float direction;
	float speed;
};