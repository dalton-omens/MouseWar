#include "BasicBullet.hpp"

BasicBullet::BasicBullet(std::shared_ptr<Game> game, int projID, int xPos, int yPos, int xVel, int yVel)
	: game(game), projID(projID), xPos(xPos), yPos(yPos), xVel(xVel), yVel(yVel)
{
	shape = std::make_unique<sf::CircleShape>((float) BULLET_RADIUS, (float) BULLET_POINT_COUNT);
	shape->setFillColor(sf::Color::Black);
	shape->setPosition((float) xPos, (float) yPos);

	windowWidth = game->window->getSize().x;
	windowHeight = game->window->getSize().y;
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
* This method applies movement based on its velocity.
* Then, it checks for collisions with other mice.
* This method is called once every update cycle.
*/
int BasicBullet::update() {
	xPos += xVel;
	yPos += yVel;
	shape->setPosition((float) xPos, (float) yPos);

	/* If this bullet travels out of bounds, remove it from the game */
	if (xPos > windowWidth || xPos < 0 || yPos > windowHeight || yPos < 0) {
		game->removeProjectile(projID);
	}
	return 0;
}

/* Draws this object to the target, which is the window. This function is part of the
* sf::Drawable class. Render.cpp calling window.draw on this object will call this method. */
void BasicBullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*shape, states);
}
