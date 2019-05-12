#include "Animation.h"
#include <iostream>

Animation::Animation()
{
}

Animation::Animation(uint spriteWidth, uint spriteHeight, glm::vec2 frameSize, glm::vec2 spacing, glm::vec2 margin, uint totalFrames, float animationSpeed, uint framesPerRow)
	: spriteWidth(spriteWidth), spriteHeight(spriteHeight), spacing(spacing), margin(margin), totalFrames(totalFrames)
{
	this->sourceRect = { 0, 0, (int)frameSize.x, (int)frameSize.y };

	this->currentFrame = 0;
	this->framesPerRow = framesPerRow != 0 ? framesPerRow : totalFrames;
	this->animationSpeed = animationSpeed * 60;
	this->timer = 0;
	this->startFrame = 0;
	this->endFrame = totalFrames-1;
	
	GotoFrame(0);
}

void Animation::Update(float deltaTime)
{
	timer += deltaTime * 60;

	if (timer >= animationSpeed)
	{
		timer = 0;
		GotoNextFrame();
	}
}

void Animation::GotoFrame(uint frame)
{
	currentFrame = std::fmin(frame, endFrame);
	currentFrame = std::fmax(frame, startFrame);

	int cel = (int)std::floor(currentFrame % framesPerRow);
	int row = (int)std::floor(currentFrame / framesPerRow);

	sourceRect.x = margin.x + (cel * sourceRect.width) + (cel * spacing.x);
	sourceRect.y = margin.y + (row * sourceRect.height) + (row * spacing.y);

	UVCoords = { (float)sourceRect.x / (float)spriteWidth,
				(float)(spriteHeight - sourceRect.GetTop()) / (float)spriteHeight,
				(float)sourceRect.GetRight() / (float)spriteWidth,
				(float)(spriteHeight - sourceRect.y) / (float)spriteHeight };
}

void Animation::GotoNextFrame() {
	GotoFrame(currentFrame < endFrame ? currentFrame + 1 : startFrame);
}
void Animation::GotoPrevFrame() {
	GotoFrame(currentFrame > startFrame ? currentFrame - 1 : endFrame);
}

int Animation::GetFrame() const {
	return currentFrame;
}
int Animation::GetStartingFrame() const {
	return startFrame;
}

void Animation::SetAnimation(int startFrame, int endFrame)
{
	this->startFrame = std::fmax(0, startFrame);
	this->endFrame = std::fmin(totalFrames-1, endFrame);

	GotoFrame(startFrame);
}

glm::vec4 Animation::GetUVCoords() const
{
	return UVCoords;
}