#include "Player.h"

Player::Player(const sf::Vector2f &size) : AnimatedSprite(size)
{
	//Initial variable values
	health = 100;
	bullets = 20;
	clips = 5;
	zombiesKilled = 0;

	//Animation
	walk.init(0, 0, 12, 9, 4, 0.1f);
	currentAnimation = &walk;
	frame = currentAnimation->getCurrentFrame();
	setTextureRect(frame);
	elapsedTime = 0.f;

	//Setup
	texture.loadFromFile("gfx/PlayerSprite.png");
	setSize(sf::Vector2f(36.f, 36.f));
	setTexture(&texture);
	setPosition(180.f, 180.f);
	position = getPosition();
	setOrigin(getSize().x / 2.f, getSize().y / 2.f);
	updateAABBWithOrigin();
}

Player::~Player()
{
}

void Player::update(float dt)
{
	//Rotate with mouse
	position = getPosition();
	target = sf::Vector2f(input->getMouseWorld()); //Update target to mouses position
	pos = position - target;
	pos = Vector::normalise(pos);
	float dx = pos.x;
	float dy = pos.y;
	rotation = (atan2(dy, dx)) * 180.f / PI;
	rotation -= 90.f;
	setRotation(rotation);

	//Movement
	if ((input->isKeyDown(sf::Keyboard::D)))
	{
		notFlipped = true;
		walk.setFlipped(notFlipped);
		velocity.x = 150.f;
		velocity.y = 0.f;
		move(velocity * dt);
	}
	if (input->isKeyDown(sf::Keyboard::A))
	{
		notFlipped = false;
		walk.setFlipped(notFlipped);
		velocity.x = -150.f;
		velocity.y = 0.f;
		move(velocity * dt);
	}
	if (input->isKeyDown(sf::Keyboard::W))
	{
		notFlipped = true;
		walk.setFlipped(notFlipped);
		velocity.y = -150.f;
		velocity.x = 0.f;
		move(velocity * dt);
	}
	if (input->isKeyDown(sf::Keyboard::S))
	{
		notFlipped = false;
		walk.setFlipped(notFlipped);
		velocity.y = 150.f;
		velocity.x = 0.f;
		move(velocity * dt);
	}

	//Animation
	if (!notFlipped && input->isKeyDown(sf::Keyboard::A) || !notFlipped && input->isKeyDown(sf::Keyboard::S))
	{
		//increment time
		elapsedTime += dt;

		//if enough time has passed move onto next frame
		if (elapsedTime >= currentAnimation->getAnimationTime())
		{
			frame.left = frame.width * -1;
			//next frame
			currentAnimation->nextFrame();
			setTextureRect(currentAnimation->getCurrentFrame());
			elapsedTime = 0.f;
		}
	}
	else if (notFlipped && input->isKeyDown(sf::Keyboard::W) || notFlipped && input->isKeyDown(sf::Keyboard::D))
	{
		//increment time
		elapsedTime += dt;

		//if enough time has passed move onto next frame
		if (elapsedTime >= currentAnimation->getAnimationTime())
		{
			//next frame
			currentAnimation->nextFrame();
			setTextureRect(currentAnimation->getCurrentFrame());
			elapsedTime = 0.f;
		}
	}
	updateAABBWithOrigin();
}


void Player::getInput(Input *in)
{
	input = in;
}

void Player::worldCollisionResponse(Sprites* sp)
{
	//Reset Velocity
	velocity.x = 0.f;
	velocity.y = 0.f;

	//Detect where the collision happened
	if ((abs(sp->getPosition().x + sp->getAABB().width / 2.f - getPosition().x)) > (abs(sp->getPosition().y + sp->getAABB().width / 2.f - getPosition().y)))
	{
		//Left or Right Side collision
		if (getPosition().x <= sp->getPosition().x)
		{
			//Left side collision
			setPosition(std::round(sp->getPosition().x - getSize().x + getOrigin().x), std::round(getPosition().y));
		}
		else
		{
			//Right side collision
			setPosition(std::round(sp->getPosition().x + sp->getSize().x + getOrigin().x), std::round(getPosition().y));
		}
	}
	else
	{
		//Top or Bottom collision
		if (getPosition().y <= sp->getPosition().y)
		{
			//Top side collision
			setPosition(std::round(getPosition().x), std::round(sp->getPosition().y - getSize().y + getOrigin().y));
		}
		else
		{
			//Bottom side collision
			setPosition(std::round(getPosition().x), std::round(sp->getPosition().y + sp->getSize().y + getOrigin().y));
		}
	}
}

void Player::enemyCollisionResponse(Sprites* sp)
{
	health -= 1;
}

void Player::setHealth(int pHealth)
{
	health = pHealth;
}

void Player::setBullets(int pBullets)
{
	bullets = pBullets;
}

void Player::setClips(int pClips)
{
	clips = pClips;
}

void Player::setZombiesKilled(int pZK)
{
	zombiesKilled = pZK;
}

void Player::reset()
{
	health = 100;
	bullets = 20;
	clips = 5;
	zombiesKilled = 0;
	setPosition(180.f, 180.f);
}