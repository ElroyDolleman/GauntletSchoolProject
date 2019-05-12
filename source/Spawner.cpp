#include "Spawner.h"
#include <random>
#include <Ghost.h>
#include <GameLevels.h>

Spawner::Spawner(SpawnableEnemies spawnableEnemy, Player& player, std::vector<Tile*>& map, std::vector<Enemy*>& enemies)
	: Enemy(player), map(map), enemies(enemies)
{
	timer = GetSpawnTime();

	animation = Animation(540, 608, { 64, 64 }, { 4, 4 }, { 0, 544 }, 3, 0, 3);

	sprite.m_MinUV = animation.GetUVCoords().xy;
	sprite.m_MaxUV = animation.GetUVCoords().zw;

	this->SetHealth(90);
	this->resistance = 3;
	this->points = 50;
}

Spawner::~Spawner()
{
	
}

void Spawner::Update(float deltaTime)
{
	timer -= deltaTime;

	if (timer <= 0)
	{
		timer = GetSpawnTime();

		int x = std::floor(position.x / 64);
		int y = std::floor(position.y / 64);

		std::vector<glm::vec2> spawnDirList = { { 1, 0 }, { 0, -1 }, { -1, 0 }, { 0, 1 } };

		for (int i = 0; i < 4; i++)
		{
			int spawnDirIndex = (int)std::round(((double)std::rand() / (RAND_MAX)) * (spawnDirList.size()-1));
			glm::vec2 dir = spawnDirList[spawnDirIndex];
			
			if (IsSpawnablePlace(x + dir.x, y + dir.y))
			{
				SpawnEnemy(x + dir.x, y + dir.y);
				break;
			}
			else
				spawnDirList.erase(spawnDirList.begin() + spawnDirIndex);
		}
	}
}

void Spawner::Attacked(float power)
{
	Enemy::Attacked(power);

	if (animation.GetFrame() < 1 && health <= 60)
		animation.GotoFrame(1);

	else if (animation.GetFrame() < 2 && health <= 30)
		animation.GotoFrame(2);

	sprite.m_MinUV = animation.GetUVCoords().xy;
	sprite.m_MaxUV = animation.GetUVCoords().zw;

	if (health == 0)
	{
		int x = std::floor(position.x / 64);
		int y = std::floor(position.y / 64);
		int index = MapData::GetTileIndex(x, y);

		map[index]->SetTileType(Tile::TileType::Floor);
	}
}

void Spawner::HitPlayer()
{
}

bool Spawner::IsInteractable() const
{
	return false;
}

void Spawner::SetPosition(glm::vec2 position)
{
	int x = (int)std::floor(position.x / 64);
	int y = (int)std::floor(position.y / 64);
	int index = MapData::GetTileIndex(x, y);

	map[index]->SetTileType(Tile::TileType::Wall);

	this->position = position;
}

float Spawner::GetSpawnTime()
{
	return 1.5f + ((double)std::rand() / (RAND_MAX) / 2) * 2;
}

void Spawner::SpawnEnemy(int gridX, int gridY)
{
	int index = MapData::GetTileIndex(gridX, gridY);

	enemies.push_back(new Ghost(GetPlayer()));
	enemies.back()->SetPosition(map[index]->GetPosition());
	map[index]->SetEnemyRef(*enemies.back());
}

bool Spawner::IsSpawnablePlace(int gridX, int gridY) const
{
	int index = MapData::GetTileIndex(gridX, gridY);

	return (map[index]->IsEmpty());
}
