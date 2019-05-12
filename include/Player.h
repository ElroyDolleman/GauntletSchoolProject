#pragma once

#include "Application.h"
#include <Entity.h>
#include <Bullet.h>

class Player : public Entity 
{
public:

	enum Character
	{
		Warrior,
		Wizard,
		Valkyrie,
		Elf
	};

	Player(Character character);
	~Player();

	void Update(float deltaTime);

	float GetWalkSpeed() const;
	float GetPower() const;
	int GetHealth() const;
	void LoseHealth(float damage);
	void Heal(float health);

	const Bullet& GetBullet() const;
	NHTV::SpriteBatch::Sprite& GetBulletSprite() const;
	void DeactivateBullet();

private:

	Bullet* bullet;

	float walkSpeed;
	float bulletSpeed;
	float resistance;
	float power;

	float health;

	Animation animation;
	Character characterType;

	glm::vec2 direction;

	void WalkingUpdate(NHTV::Application& app, float deltaTime);
	void ShootingUpdate(NHTV::Application& app, float deltaTime);

	int GetStartFrame(glm::vec2 direction) const;
};