#include "Enemy.h";

Enemy::Enemy(Player& player)
{
	this->player = &player;

	this->resistance = 1;
	this->power = 20;
	this->speed = 100;
	this->points = 20;

	this->SetHealth(100);

	this->sprite.m_Size = { 64, 64 };
	this->sprite.m_Origin = { 0, 0 };

	this->SetHitbox(0, 0, 64, 64);
}

void Enemy::Update(float deltaTime)
{
	// Animation
	if (direction != glm::vec2{ 0, 0 })
	{
		animation.Update(deltaTime);

		// Change animation
		if (GetStartFrame(direction) != animation.GetStartingFrame())
		{
			int startFrame = GetStartFrame(direction);
			animation.SetAnimation(startFrame, startFrame + 2);
		}

		sprite.m_MinUV = animation.GetUVCoords().xy;
		sprite.m_MaxUV = animation.GetUVCoords().zw;
	}
}

void Enemy::MoveTowards(float posX, float posY, float deltaTime)
{
	float velocity = speed * deltaTime;

	direction = { 0, 0 };

	if (position.x < posX - velocity) direction.x = 1;
	else if (position.x > posX + velocity) direction.x = -1;

	if (position.y < posY - velocity) direction.y = 1;
	else if (position.y > posY + velocity) direction.y = -1;

	position.x += velocity * direction.x;
	position.y += velocity * direction.y;
}

void Enemy::MoveTowards(glm::vec2 position, float deltaTime)
{
	MoveTowards(position.x, position.y, deltaTime);
}

void Enemy::Attacked(float power) {
	health = std::fmax(health - power/resistance, 0);
}
float Enemy::GetHealth() const {
	return health;
}
float Enemy::GetMaxHealth() const {
	return maxHealth;
}
float Enemy::GetPower() const {
	return power;
}
int Enemy::GetPoints() const {
	return points;
}
float Enemy::GetSpeed() const {
	return speed;
}

bool Enemy::IsInteractable() const
{
	return true;
}

void Enemy::SetPosition(glm::vec2 position)
{
	this->position = position;
}

void Enemy::HitPlayer()
{
	GetPlayer().LoseHealth(GetPower());
}

int Enemy::GetStartFrame(glm::vec2 direction) const
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

float Enemy::DistanceTo(glm::vec2 pos) const
{
	float valueX = pos.x - position.x;
	float valueY = pos.y - position.y;
	return std::sqrt((valueX * valueX) + (valueY * valueY));
}

Player& Enemy::GetPlayer() const
{
	return *player;
}

void Enemy::SetHealth(float maxHealth)
{
	this->maxHealth = maxHealth;
	this->health = maxHealth;
}
