#include <Application.h>
#include <iostream>
#include "Player.h"

Player::Player(Character character)
{
	glm::vec2 animationMargin;
	Rectangle bulletSource;
	characterType = character;

	switch (character)
	{
	case Player::Warrior:
		walkSpeed = 220;
		bulletSpeed = 600;
		resistance = 1.5f;
		power = 60;

		animationMargin = { 204, 0 };
		bulletSource = { 816, 68, 64, 64 };
		break;
	case Player::Wizard:
		walkSpeed = 230;
		bulletSpeed = 650;
		resistance = 1;
		power = 45;

		animationMargin = { 612, 0 };
		bulletSource = { 816, 204, 64, 64 };
		break;
	case Player::Valkyrie:
		walkSpeed = 250;
		bulletSpeed = 700;
		resistance = 1.75f;
		power = 38;

		animationMargin = { 408, 0 };
		bulletSource = { 816, 136, 64, 64 };
		break;
	case Player::Elf:
		walkSpeed = 300;
		bulletSpeed = 950;
		resistance = 1;
		power = 35;

		animationMargin = { 0, 0 };
		bulletSource = { 816, 0, 64, 64 };
		break;
	}
	
	health = 500;

	// Animation
	animation = Animation(880, 540, { 64, 64 }, { 4, 4 }, animationMargin, 25, .2f, 3);
	animation.SetAnimation(0, 2);

	sprite.m_Size = { 64, 64 };
	sprite.m_Origin = { 0, 0 };

	sprite.m_MinUV = animation.GetUVCoords().xy;
	sprite.m_MaxUV = animation.GetUVCoords().zw;

	// Bullet
	bullet = new Bullet(position.x, position.y, 0, bulletSpeed);
	glm::vec4 bulletUV = { (float)bulletSource.x / 880.0f, (540.0f - (float)bulletSource.GetBottom()) / 540.0f, (float)bulletSource.GetRight() / 880.0f, (540.0f - (float)bulletSource.GetTop()) / 540.0f };
	bullet->sprite.m_MinUV = bulletUV.xy;
	bullet->sprite.m_MaxUV = bulletUV.zw;
	bullet->SetActive(false);

	// Hitbox
	SetHitbox({ 0, 0, 64, 64 });
}

Player::~Player()
{
	delete bullet;
}

void Player::Update(float deltaTime)
{
	NHTV::Application& app = NHTV::Application::GetInstance();

	WalkingUpdate(app, deltaTime);
	ShootingUpdate(app, deltaTime);
}

void Player::WalkingUpdate(NHTV::Application & app, float deltaTime)
{
	LoseHealth(deltaTime);

	if (app.IsKeyDown(NHTV::D))
		direction.x = 1;
	else if (app.IsKeyDown(NHTV::A))
		direction.x = -1;

	if (app.IsKeyDown(NHTV::W))
		direction.y = 1;
	else if (app.IsKeyDown(NHTV::S))
		direction.y = -1;

	position.x += walkSpeed * deltaTime * direction.x;
	position.y += walkSpeed * deltaTime * direction.y;

	// Animation
	if (direction != glm::vec2{ 0, 0 })
	{
		animation.Update(deltaTime);

		// Change animation
		if (GetStartFrame(direction) != animation.GetStartingFrame())
		{
			int startFrame = GetStartFrame(direction);
			animation.SetAnimation(startFrame, startFrame+2);
		}

		sprite.m_MinUV = animation.GetUVCoords().xy;
		sprite.m_MaxUV = animation.GetUVCoords().zw;
	}

	direction.x = 0;
	direction.y = 0;
}

void Player::ShootingUpdate(NHTV::Application& app, float deltaTime)
{
	if (app.IsKeyDown(NHTV::SPACE) && !bullet->IsActive())
	{
		bullet->position = { position.x + GetHitbox().width/2, position.y + GetHitbox().height/2 };
		bullet->SetActive(true);
		bullet->SetDirection(animation.GetStartingFrame() / 3 * (-45));
	}

	if (bullet->IsActive())
	{
		bullet->Update(deltaTime);

		if (characterType == Warrior)
			bullet->sprite.m_Rotation -= deltaTime * 12.5f;
	}
}

float Player::GetWalkSpeed() const {
	return walkSpeed;
}
float Player::GetPower() const {
	return power;
}

int Player::GetHealth() const {
	return (int)std::round(health);
}
void Player::LoseHealth(float damage) 
{
	health = std::fmax(0, health - damage / resistance);

	
}

void Player::Heal(float health) {
	this->health += health;
}

const Bullet& Player::GetBullet() const {
	return *bullet;
}
NHTV::SpriteBatch::Sprite& Player::GetBulletSprite() const {
	return bullet->sprite;
}
void Player::DeactivateBullet() {
	bullet->SetActive(false);
}

int Player::GetStartFrame(glm::vec2 direction) const
{
	if (direction == glm::vec2{ 1, 0 }) return 0;
	else if (direction == glm::vec2{ 1, -1 }) return 3;
	else if (direction == glm::vec2{ 0, -1 }) return 6;
	else if (direction == glm::vec2{ -1, -1 }) return 9;
	else if (direction == glm::vec2{ -1, 0 }) return 12;
	else if (direction == glm::vec2{ -1, 1 }) return 15;
	else if (direction == glm::vec2{ 0, 1 }) return 18;
	else if (direction == glm::vec2{ 1, 1 }) return 21;

	return 0;
}
