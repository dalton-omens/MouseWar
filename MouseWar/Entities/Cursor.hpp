#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "../Game.hpp"
#include "Entity.hpp"

#define AVG_BUFFER_LEN 50
#define PI 3.141592653589793238463

class Game; // find out why this is necessary

class Cursor : public Entity {
public:
	sf::Color *color;
	const unsigned short mouseHeight = 29;
	const unsigned short mouseWidth = 23;

	Cursor(std::shared_ptr<Game> game, sf::Color* color_in);

	int getxPos() override;
	int getyPos() override ;
	float getRotation();
	void setxPos(int input) override;
	void setyPos(int input) override;
	void getInputX(int input);
	void getInputY(int input);

	int update();

	void fireBasicBullet();
	void queueBasicBullet();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	float rotation;
	int windowWidth, windowHeight;
	int xAvgBuffer[AVG_BUFFER_LEN];
	int yAvgBuffer[AVG_BUFFER_LEN];
	unsigned int runningAvgCounter;
	int xInputs; // since last update
	int yInputs;
	bool basicBulletQueued = false;

	/* Shape is constantly updated with this Cursor's current state */
	std::unique_ptr<sf::ConvexShape> shape;

	/* Internal move functions. Cursor should be moved by getting input i.e. getInputX() */
	void moveX(int input);
	void moveY(int input);

	sf::Vector2<float> getAverageMoves();
	void setRotation();
};