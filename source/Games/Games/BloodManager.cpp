#include "BloodManager.h"

BloodManager::BloodManager()
{
	texture.loadFromFile("gfx/Blood.png");

	for (int i = 0; i < 100; i++)
	{
		blood.push_back(Blood());
		blood[i].setAlive(false);
		blood[i].setSize(sf::Vector2f(32.f, 32.f));
		blood[i].setTexture(&texture);
		blood[i].setPosition(100.f, 100.f);
		blood[i].setOrigin(blood[i].getSize().x / 2.f, blood[i].getSize().y / 2.f);
	}
}

BloodManager::~BloodManager()
{
}

//Spawn new blood
//Find "dead" blood, make alive, move to given spawn point
void BloodManager::spawn(float x, float y)
{
	for (int i = 0; i < blood.size(); i++)
	{
		if (!blood[i].isAlive())
		{
			blood[i].setAlive(true);
			blood[i].setPosition(sf::Vector2f(x, y));
			return;
		}
	}
}

void BloodManager::update()
{

}

//Render all alive blood
void BloodManager::render(sf::RenderWindow* window)
{
	for (int i = 0; i < blood.size(); i++)
	{
		if (blood[i].isAlive())
		{
			window->draw(blood[i]);
		}
	}
}

void BloodManager::reset()
{
	for (int i = 0; i < blood.size(); i++)
	{
		blood[i].setAlive(false);
	}
}