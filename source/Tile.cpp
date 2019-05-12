#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(glm::vec2 position, Rectangle source, int tilesetWidth, int tilesetHeight)
	: position(position), width(source.width), height(source.height)
{
	sprite.m_Origin = { 0, 0 };
	sprite.m_Size = { width, height };

	glm::vec4 UVCoords = Rectangle::SourceRectToUVCoords(source, tilesetWidth, tilesetHeight);
	sprite.m_MinUV = UVCoords.xy;
	sprite.m_MaxUV = UVCoords.zw;

	tileType = TileType::Floor;

	enemy = NULL;
	pickUp = NULL;
}

Tile::~Tile()
{
	if (ContainsPickUp())
		delete pickUp;
}


// SET METHODS //

void Tile::SetPickUp(PickUp pickUp)
{
	this->pickUp = new PickUp();
	*this->pickUp = pickUp;
}

void Tile::SetEnemyRef(Enemy& enemy)
{
	this->enemy = &enemy;
}

void Tile::SetTileType(TileType tileType)
{
	this->tileType = tileType;
}


// GET METHODS //

const PickUp Tile::GetPickUp() const {
	return *pickUp;
}
const Enemy& Tile::GetEnemy() const {
	return *enemy;
}

Rectangle Tile::GetHitbox() const
{
	return{ (int)position.x, (int)position.y, width, height };
}

NHTV::SpriteBatch::Sprite Tile::GetSprite() const
{
	return sprite;
}

glm::vec2 Tile::GetPosition() const
{
	return position;
}


// DELETE METHODS //

void Tile::DeletePickUp()
{
	delete pickUp;
	pickUp = NULL;
}

void Tile::DeleteEnemyRef()
{
	enemy = NULL;
}


// CHECK METHODS //

bool Tile::IsSolid() const
{
	return (tileType == TileType::Wall || tileType == TileType::Door);
}

bool Tile::IsStairs() const
{
	return (tileType == TileType::Stairs);
}

bool Tile::IsDoor() const
{
	return (tileType == TileType::Door);
}

bool Tile::ContainsPickUp() const
{
	return (pickUp != nullptr);
}

bool Tile::ContainsEnemy() const
{
	return (enemy != nullptr);
}

bool Tile::IsEmpty() const
{
	return (!IsSolid() && !ContainsEnemy() && !ContainsPickUp());
}


// OTHER METHODS //

void Tile::CopyTile(const Tile tile)
{
	this->sprite = tile.sprite;
	this->tileType = tile.tileType;
}
