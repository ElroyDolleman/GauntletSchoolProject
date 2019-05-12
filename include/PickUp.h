#pragma once
#include <SpriteBatch.h>

struct PickUp
{
public:

	enum PickUpType
	{
		Key,
		Treasure,
		Food
	};

	PickUp(PickUpType pickUpType = PickUpType::Key, int pickUpValue = 1);

	NHTV::SpriteBatch::Sprite sprite;

	int pickUpValue;
	PickUpType pickUpType;
};