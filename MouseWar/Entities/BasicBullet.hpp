#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Entity.hpp"

#define BULLET_RADIUS 100
#define BULLET_POINT_COUNT 20

class BasicBullet : public Entity {
public:
	BasicBullet(int xPos, int yPos, int xVel, int yVel);

	int update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	int xPos, yPos;
	int xVel, yVel;

	std::unique_ptr<sf::CircleShape> shape;
};