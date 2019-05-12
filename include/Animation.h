#pragma once

#include <SpriteBatch.h>
#include <Rectangle.h>

typedef unsigned int uint;

struct Animation
{
public:

	Animation();
	Animation(uint spriteWidth, uint spriteHeight, glm::vec2 frameSize, glm::vec2 spacing, glm::vec2 margin, uint totalFrames, float animationSpeed, uint framesPerRow = 0);

	void Update(float deltaTime);
	void GotoFrame(uint frame);
	void GotoNextFrame();
	void GotoPrevFrame();
	int GetFrame() const;
	int GetStartingFrame() const;

	void SetAnimation(int startFrame, int endFrame);
	
	glm::vec4 GetUVCoords() const;

private:

	int spriteWidth, spriteHeight;
	glm::vec2 margin, spacing;
	Rectangle sourceRect;

	int startFrame, endFrame;
	int currentFrame;
	int totalFrames;
	int framesPerRow;
	float animationSpeed;
	float timer;

	glm::vec4 UVCoords;
};