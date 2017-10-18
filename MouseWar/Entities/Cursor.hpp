#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <queue>
#include "../Game.hpp"

#define AVG_BUFFER_LEN 50
#define PI 3.141592653589793238463

class Game; // find out why this is necessary

class Cursor {
public:
	sf::Color *color;
	const unsigned short mouseHeight = 29;
	const unsigned short mouseWidth = 23;

	Cursor(std::shared_ptr<Game> game, sf::Color* color_in);

	unsigned int getXpos();
	unsigned int getYpos();
	float getRotation();
	void setXpos(int input);
	void setYpos(int input);
	void getInputX(int input);
	void getInputY(int input);

	int update();

	void fireBasicBullet();
	void queueBasicBullet();

private:
	int xPos, yPos;
	float rotation;
	int windowWidth, windowHeight;
	int xAvgBuffer[AVG_BUFFER_LEN];
	int yAvgBuffer[AVG_BUFFER_LEN];
	unsigned int runningAvgCounter;
	std::queue<int> xInputs;
	std::queue<int> yInputs;
	bool basicBulletQueued = false;

	void moveX(int input);
	void moveY(int input);

	sf::Vector2<float> getAverageMoves();
	void setRotation();
};