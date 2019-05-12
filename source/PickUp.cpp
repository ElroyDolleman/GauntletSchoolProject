#include "..\include\PickUp.h"

PickUp::PickUp(PickUpType pickUpType, int pickUpValue)
{
	this->pickUpValue = pickUpValue;
	this->pickUpType = pickUpType;
	this->sprite.m_Size = { 64, 64 };
	this->sprite.m_Origin = { 0, 0 };
}