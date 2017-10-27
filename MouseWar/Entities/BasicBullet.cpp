#include "BasicBullet.hpp"

BasicBullet::BasicBullet(int xPos, int yPos, int xVel, int yVel)
	: xPos(xPos), yPos(yPos), xVel(xVel), yVel(yVel)
{
	shape = std::make_unique<sf::CircleShape>(BULLET_RADIUS, BULLET_POINT_COUNT);
	shape->setFillColor(sf::Color::Black);
	shape->setPosition(xPos, yPos);
}

int BasicBullet::getxPos() {
	return xPos;
}

int BasicBullet::getyPos() {
	return yPos;
}

void BasicBullet::setxPos(int input) {
	xPos = input;
}

void BasicBullet::setyPos(int input) {
	yPos = input;
}

/* Update this bullet in game logic.
* This method applies movement based on its velocity and direction.
* Then, it checks for collisions with other mice.
* This method is called once every update cycle.
*/
int BasicBullet::update() {
	return 0;
}

/* Draws this object to the target, which is the window. This function is part of the
* sf::Drawable class. Render.cpp calling window.draw on this object will call this method. */
void BasicBullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*shape, states);
}
