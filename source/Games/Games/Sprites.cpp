#include "Sprites.h"

Sprites::~Sprites()
{
}

Sprites::Sprites(const sf::Vector2f & size) : RectangleShape(size)
{
}

void Sprites::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}

void Sprites::setVelocity(float vx, float vy)
{
	velocity.x = vx;
	velocity.y = vy;
}

sf::Vector2f Sprites::getVelocity()
{
	return velocity;
}

sf::FloatRect Sprites::getAABB()
{
	return AABB;
}

void Sprites::updateAABB()
{
	//Axis aligned bounding box, based on sprite size and position.
	//Shape could be smaller/larger and offset if required.
	//Can be overwriten by child classes
	AABB.left = getPosition().x;
	AABB.top = getPosition().y;
	AABB.width = getSize().x;
	AABB.height = getSize().y;
}

void Sprites::updateAABBWithOrigin()
{
	//Axis aligned bounding box, based on sprite size, position and origin.
	//Shape could be smaller/larger and offset if required.
	//Can be overwriten by child classes
	AABB.left = getPosition().x - getOrigin().x;
	AABB.top = getPosition().y - getOrigin().y;
	AABB.width = getSize().x;
	AABB.height = getSize().y;
}

//Response function, what the sprite does based on collision
//Colliding object is passed in for information
void Sprites::collisionResponse()
{
	//e.g. compare sprite positions to determine new velocity direction.
	//e.g. checking sprite type (world, enemy, bullet etc) so response is based on that.
}
