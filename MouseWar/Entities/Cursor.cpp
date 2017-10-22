#include "Cursor.hpp"

Cursor::Cursor(std::shared_ptr<Game> game, sf::Color* color_in) {
	windowWidth = game->window->getSize().x;
	windowHeight = game->window->getSize().y;
	xPos = windowWidth / 2;
	yPos = windowHeight / 2;
	color = color_in;
	runningAvgCounter = 0;
	rotation = 0;

	for (int i = 0; i < AVG_BUFFER_LEN; i++)
	{
		xAvgBuffer[i] = 0;
		yAvgBuffer[i] = 0;
	}

	/* Initialize the shape to be drawn in draw() */
	shape = std::make_unique<sf::ConvexShape>(10);
	shape->setPointCount(7);
	shape->setPoint(0, sf::Vector2f(0, 0));
	shape->setPoint(1, sf::Vector2f(11, 21));
	shape->setPoint(2, sf::Vector2f(3, 18));
	shape->setPoint(3, sf::Vector2f(3, 29));
	shape->setPoint(4, sf::Vector2f(-3, 29));
	shape->setPoint(5, sf::Vector2f(-3, 18));
	shape->setPoint(6, sf::Vector2f(-11, 21));
	shape->setRotation(rotation);
	shape->setFillColor(*color);
	shape->setPosition(xPos, yPos);
}

int Cursor::getxPos() {
	return this->xPos;
}

int Cursor::getyPos() {
	return this->yPos;
}

float Cursor::getRotation() {
	return this->rotation;
}


/* Manually set x position of this cursor. */
void Cursor::setxPos(int input) {
	if (input < 0) {
		input = 0;
	}
	else if (input > windowWidth) {
		input = windowWidth;
	}
	xPos = input;
}

/* Manually set y position of this cursor. */
void Cursor::setyPos(int input) {
	if (input < 0) {
		input = 0;
	}
	else if (input > windowHeight) {
		input = windowHeight;
	}
	yPos = input;
}

/* Receive input from user, put the input to the move queue to be used in update() */
void Cursor::getInputX(int input) {
	xInputs.push(input);
}

/* Receive input from user, put the input to the move queue to be used in update() */
void Cursor::getInputY(int input) {
	yInputs.push(input);
}

/* Move this cursor in x direction. Private method. */
void Cursor::moveX(int input) {
	xPos = xPos + input;
	if (xPos < mouseWidth/2) {
		xPos = mouseWidth/2;
	}
	else if (xPos > windowWidth - mouseWidth/2) {
		xPos = windowWidth - mouseWidth/2;
	}

	xAvgBuffer[runningAvgCounter] = input;
	yAvgBuffer[runningAvgCounter] = 0;
	runningAvgCounter = (runningAvgCounter + 1) % AVG_BUFFER_LEN;
}

/* Move this cursor in y direction. Private method. */
void Cursor::moveY(int input) {
	yPos += input;
	if (yPos < 0) {
		yPos = 0;
	}
	else if (yPos > windowHeight - mouseHeight) {
		yPos = windowHeight - mouseHeight;
	}
	yAvgBuffer[runningAvgCounter] = input;
	xAvgBuffer[runningAvgCounter] = 0;
	runningAvgCounter = (runningAvgCounter + 1) % AVG_BUFFER_LEN;
}

/* Compute the average movement in x and y over the last AVG_BUFFER_LEN inputs 
 * Used for rotation */
sf::Vector2<float> Cursor::getAverageMoves() {
	float sumX = 0;
	float sumY = 0;
	for (int i = 0; i < AVG_BUFFER_LEN; i++)
	{
		sumX += xAvgBuffer[i];
		sumY += yAvgBuffer[i];
	}

	return sf::Vector2<float>(sumX / AVG_BUFFER_LEN, sumY / AVG_BUFFER_LEN);
}

/* Computes the rotation of this cursor based on previous moves
 * TODO: make this way more efficient (no trig functions!) */
void Cursor::setRotation() {
	sf::Vector2<float> averages = getAverageMoves();
	rotation = std::round(std::atan2(averages.y, averages.x) * 180 / PI) + 90;
}

/* Update this cursor in game logic.
 * This method gets all movements queued from user input, and applies them to the cursor.
 * It also processes all other queued actions.
 * This method is called once every update cycle.
 */
int Cursor::update() {
	while (!xInputs.empty()) {
		moveX(xInputs.front());
		xInputs.pop();
	}

	while (!yInputs.empty()) {
		moveY(yInputs.front());
		yInputs.pop();
	}
	setRotation();

	/* Update the rendering's attributes */
	shape->setPosition(xPos, yPos);
	shape->setRotation(rotation);
	return 0;
}

/* Draws this object to the target, which is the window. This function is part of the
 * sf::Drawable class. Render.cpp calling window.draw on this object will call this method. */
void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*shape, states);
}

/* Fire a basic bullet, when updating game logic. */
void Cursor::fireBasicBullet() {
			
}

/* Place a basic bullet into the action queue. */
void Cursor::queueBasicBullet() {
	basicBulletQueued = true;
}