#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Entity.hpp"
#include "../Game.hpp"

#define BULLET_RADIUS 4
#define BULLET_POINT_COUNT 20

class Game;

class BasicBullet : public Entity_old {
public:
	BasicBullet(std::shared_ptr<Game> game, int projID, int xPos, int yPos, int xVel, int yVel);

	int getxPos() override;
	int getyPos() override;
	void setxPos(int input) override;
	void setyPos(int input) override;

	int update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	int projID;
	std::shared_ptr<Game> game;
	int windowWidth, windowHeight;

	int xPos, yPos;
	int xVel, yVel;

	std::unique_ptr<sf::CircleShape> shape;
};