#pragma once
#include "SFML/Graphics.hpp"

class Animation
{
public:
	Animation();
	~Animation();

	void init(int left, int top, int width, int height, int frames, float speed);

	sf::IntRect getCurrentFrame();
	float getAnimationTime() { return animationSpeed; };
	void nextFrame();
	void setFlipped(bool flip);

protected:
	sf::IntRect frame;
	int numberOfFrames;
	int currentFrame;
	bool flipped = true;
	float animationSpeed;
};

