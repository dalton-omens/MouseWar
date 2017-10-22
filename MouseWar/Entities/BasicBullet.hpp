#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Entity.hpp"

#define BULLET_RADIUS 100
#define BULLET_POINT_COUNT 20

class BasicBullet : public Entity {
public:
	BasicBullet(int xPos, int yPos, double vel, double rotation);

	int update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	int xPos, yPos;
	double vel, rotation;

	std::unique_ptr<sf::CircleShape> shape;
};