#include <GameState.h>
#include <iostream>
#include <GameLevels.h>
#include <StateManager.h>

using namespace NHTV;

Player::Character playableCharacter = Player::Character::Elf;

GameState::GameState()
{
	// Player
	playerBatch = new SpriteBatch("../resources/images/PlayerSheet.png");
	player = new Player(playableCharacter);
	playerBatch->AddSprite(player->sprite);
	playerBatch->AddSprite(player->GetBulletSprite());

	// Level
	tilesBatch = new SpriteBatch("../resources/images/DungeonTileset.png");
	currentLevel = 1;

	// Enemies
	enemyBatch = new SpriteBatch("../resources/images/EnemySheet.png");

	// UI
	gameUI = new GameUI();
	gameUIBatch = new SpriteBatch("../resources/images/UISheet.png");

	Initialize();
}

GameState::~GameState()
{
	delete view;
	delete gameUI;
	delete enemyBatch;
	delete playerBatch;
	delete gameUIBatch;

	for (Enemy* enemy : enemies)
		delete enemy;
	enemies.clear();

	delete player;
}

void GameState::Initialize()
{
	levelComplete = false;

	MapData::SetMap(currentLevel, *player, map, enemies);

	player->position = MapData::GetPlayerStartingPosition();

	if (view != nullptr)
		delete view;

	// View
	view = new View({ 0, 0, MapData::GetMapWidth() * 64, MapData::GetMapHeight() * 64 }, { 128, 1280, 960, 720 });
	view->SetCenterPosition(player->position);
}

void GameState::Update(float deltaTime)
{
	player->Update(deltaTime);

	UpdateCollisionCheck(deltaTime);
	UpdateView();
	UpdateEnemies(deltaTime);

	if (player->GetHealth() == 0)
		StateManager::ChangeState(StateManager::GameStates::Menu);

	else if (levelComplete)
	{
		currentLevel++;
		this->Initialize();
	}
}

void GameState::UpdateCollisionCheck(float deltaTime)
{
	Rectangle collider = Rectangle::Empty();
	glm::vec2 beginPos, endPos;

	TileCoordsInRectangle(beginPos, endPos, player->GetHitbox());
	for (int x = beginPos.x; x <= endPos.x; x++)
		for (int y = beginPos.y; y <= endPos.y; y++)
		{
			Tile& tile = GetTile(x, y);

			if (tile.IsStairs() && player->GetHitbox().Intersects(tile.GetHitbox()))
				levelComplete = true;

			else if (tile.IsSolid() && player->GetHitbox().Intersects(tile.GetHitbox()))
			{
				if (tile.IsDoor() && gameUI->keys > 0)
				{
					gameUI->keys--;

					for (int i = -1; i <= 1; i += 1)
						for (int x2 = i; GetTile(x + x2, y).IsDoor(); x2 += i)
						{
							GetTile(x + x2, y).CopyTile(GetPlayerTile());

							for (int j = -1; j <= 1; j += 2)
								for (int y2 = j; GetTile(x + x2, y + y2).IsDoor(); y2 += j)
									GetTile(x + x2, y + y2).CopyTile(GetPlayerTile());
						}
				}

				else if (collider != Rectangle::Empty())
				{
					Rectangle newCollider = GetCollider(collider, tile.GetHitbox());

					if (newCollider == collider)
						player->CheckCollision(tile.GetHitbox(), player->GetWalkSpeed() * deltaTime);
					else
						collider = newCollider;
				}
				else
					collider = tile.GetHitbox();
			}
			else if (tile.ContainsPickUp())
			{
				switch (tile.GetPickUp().pickUpType)
				{
				case PickUp::Key: gameUI->keys += tile.GetPickUp().pickUpValue; break;
				case PickUp::Food: player->Heal(tile.GetPickUp().pickUpValue); break;
				case PickUp::Treasure: gameUI->score += tile.GetPickUp().pickUpValue; break;
				}

				tile.DeletePickUp();
			}
		}
	if (collider != Rectangle::Empty())
		player->CheckCollision(collider, player->GetWalkSpeed() * deltaTime);

	// Bullet Collision
	TileCoordsInRectangle(beginPos, endPos, player->GetBullet().GetHitbox());
	for (int x = beginPos.x; x <= endPos.x; x++)
		for (int y = beginPos.y; y <= endPos.y; y++)
		{
			Tile& tile = GetTile(x, y);

			if (tile.IsSolid() && !tile.ContainsEnemy() && BulletCollidesWith(tile.GetHitbox()))
				player->DeactivateBullet();
		}
}

void GameState::UpdateView()
{
	view->SetCenterPosition(player->GetHitbox().GetCenter());

	if (!view->GetScreenArea().Intersects(player->GetBullet().GetHitbox()))
		player->DeactivateBullet();
}

void GameState::UpdateEnemies(float deltaTime)
{
	for (int enemyIndex = 0; enemyIndex < enemies.size(); enemyIndex++)
	{
		Enemy* enemy = enemies[enemyIndex];

		if (view->GetScreenArea().Intersects(enemy->GetHitbox()))
		{
			GetEnemyTile(*enemy).DeleteEnemyRef();

			enemy->Update(deltaTime);

			Rectangle collider = Rectangle::Empty();
			glm::vec2 beginPos, endPos;
			TileCoordsInRectangle(beginPos, endPos, enemy->GetHitbox());

			for (int x = beginPos.x - 1; x <= endPos.x; x++)
				for (int y = beginPos.y - 1; y <= endPos.y; y++)
				{
					Tile& tile = GetTile(x, y);

					// Tile Collision
					if (enemy->IsInteractable() && tile.IsSolid() && enemy->GetHitbox().Intersects(tile.GetHitbox()))
					{
						Rectangle newCollider = GetCollider(collider, tile.GetHitbox());

						if (newCollider == collider)
							enemy->CheckCollision(tile.GetHitbox(), enemy->GetSpeed() * deltaTime);
						else
							collider = newCollider;
					}

					// Enemy Collision
					if (enemy->IsInteractable() && tile.ContainsEnemy())
					{
						Rectangle enHitbox = tile.GetEnemy().GetHitbox();

						if (enemy->GetHitbox().Intersects(enHitbox))
							enemy->CheckCollision(tile.GetEnemy().GetHitbox(), enemy->GetSpeed() * deltaTime);
					}
				}

			if (collider != Rectangle::Empty())
				enemy->CheckCollision(collider, enemy->GetSpeed() * deltaTime);
			// Player Collision
			if (player->GetHitbox().Intersects(enemy->GetHitbox()))
				enemy->HitPlayer();

			// Bullet Collision
			if (player->GetBullet().IsActive())
				if (enemy->GetHitbox().Intersects(player->GetBullet().GetHitbox()))
				{
					player->DeactivateBullet();
					enemy->Attacked(player->GetPower());
				}

			if (enemy->GetHealth() == 0)
			{
				gameUI->score += enemy->GetPoints();

				delete enemy;
				enemies.erase(enemies.begin() + enemyIndex);
				enemyIndex--;
			}
			else
				GetEnemyTile(*enemy).SetEnemyRef(*enemy);
		}
	}
}

void GameState::Draw()
{
	std::vector<SpriteBatch::Sprite> tileSprites;
	std::vector<SpriteBatch::Sprite> pickupSprites;
	glm::vec2 beginPos, endPos;

	TileCoordsInRectangle(beginPos, endPos, view->GetScreenArea());
	for (int x = beginPos.x; x <= endPos.x; x++)
		for (int y = beginPos.y; y <= endPos.y; y++)
		{
			Tile& tile = GetTile(x, y);

			SpriteBatch::Sprite tileSprite = tile.GetSprite();

			tileSprite.m_Position = view->InScreenPosition(tile.GetPosition());
			tileSprites.push_back(tileSprite);

			if (tile.ContainsPickUp())
			{
				SpriteBatch::Sprite pickUpS = tile.GetPickUp().sprite;
				pickUpS.m_Position = tileSprite.m_Position;

				pickupSprites.push_back(pickUpS);
			}
		}

	tilesBatch->Draw(tileSprites);
	playerBatch->Draw(pickupSprites);

	// Enemies
	std::vector<NHTV::SpriteBatch::Sprite> enemySprites;

	for (Enemy* enemy : enemies)
		if (view->GetScreenArea().Intersects(enemy->GetHitbox()))
		{
			enemy->sprite.m_Position = view->InScreenPosition(enemy->position);
			enemySprites.push_back(enemy->sprite);
		}

	enemyBatch->Draw(enemySprites);

	// Player
	player->GetBulletSprite().m_Position = view->InScreenPosition(player->GetBullet().position);
	player->sprite.m_Position = view->InScreenPosition(player->position);

	playerBatch->GetSprite(0) = player->sprite;
	playerBatch->GetSprite(1) = player->GetBulletSprite();

	playerBatch->Draw();

	// UI
	gameUI->Draw(*gameUIBatch);

	application->SetFont("../resources/fonts/invaders.fnt");
	application->DrawString(gameUI->GetScoreText().c_str(), gameUI->GetPosition().x + 56, 600);
	application->DrawString(gameUI->GetHealthText(player->GetHealth()).c_str(), gameUI->GetPosition().x + 56, 560);
}

glm::vec2 GameState::ToGridLocation(glm::vec2 position)
{
	glm::vec2 output;
	output.x = std::floor(position.x / 64);
	output.y = std::floor(position.y / 64);

	output.x = std::fmax(std::fmin(output.x, MapData::GetMapWidth() - 1), 0);
	output.y = std::fmax(std::fmin(output.y, MapData::GetMapHeight() - 1), 0);

	return output;
}

Tile& GameState::GetTile(int x, int y)
{
	return *map[MapData::GetTileIndex(x, y)];
}

Tile& GameState::GetTile(glm::vec2 position)
{
	return GetTile((int)position.x, (int)position.y);
}

Tile& GameState::GetPlayerTile()
{
	glm::vec2 playerGridPos = ToGridLocation(player->GetHitbox().GetCenter());

	return GetTile(playerGridPos);
}

Tile & GameState::GetEnemyTile(const Enemy& enemy)
{
	glm::vec2 enemyGridPos = ToGridLocation(enemy.GetHitbox().GetCenter());

	return GetTile(enemyGridPos);
}

void GameState::TileCoordsInRectangle(glm::vec2 &beginPos, glm::vec2 &endPos, Rectangle rect)
{
	beginPos = ToGridLocation(rect.GetLocation());
	endPos = ToGridLocation(rect.GetTopRightCorner());
}

Rectangle GameState::GetCollider(Rectangle collider, Rectangle hitbox)
{
	if (collider != Rectangle::Empty())
	{
		if ((collider.x == hitbox.x && collider.GetRight() == hitbox.GetRight())
			|| (collider.y == hitbox.y && collider.GetTop() == hitbox.GetTop()))
			collider = Rectangle::Union(collider, hitbox);
	}
	else
		collider = hitbox;

	return collider;
}

bool GameState::BulletCollidesWith(Rectangle collider) {
	return player->GetBullet().IsActive() && player->GetBullet().GetHitbox().Intersects(collider);
}

void GameState::SetPlayableCharacter(Player::Character character)
{
	playableCharacter = character;
}