// Blood Manager
// Maintains vector of Blood for spawning in game
#pragma once
#include "Blood.h"
#include "Vector.h"
#include <math.h>
#include <vector>

class BloodManager
{
public:
	BloodManager();
	~BloodManager();

	void spawn(float x, float y);
	void update();
	void render(sf::RenderWindow* window);
	void reset();
	std::vector<Blood>* getBloodVector() { return &blood; };

private:
	std::vector<Blood> blood;
	sf::Texture texture;
};

