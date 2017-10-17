#include <SFML/Graphics.hpp>
#include <cmath>
#include <queue>
//#include "BasicBullet"

#define AVG_BUFFER_LEN 50
#define PI 3.141592653589793238463

class Cursor {

	
	private:
		int xPos, yPos;
		int windowWidth, windowHeight;
		int xAvgBuffer[AVG_BUFFER_LEN];
		int yAvgBuffer[AVG_BUFFER_LEN];
		unsigned int runningAvgCounter;
		std::queue<int> xInputs;
		std::queue<int> yInputs;
		bool basicBulletQueued = false;


	public:
		float rotation;

		Cursor(unsigned int windowWidth_in, unsigned int windowHeight_in, sf::Color* color_in) {
			xPos = 0;
			yPos = 0;
			windowWidth = windowWidth_in;
			windowHeight = windowHeight_in;
			color = color_in;
			runningAvgCounter = 0;
			rotation = 0;

			for (int i = 0; i < AVG_BUFFER_LEN; i++)
			{
				xAvgBuffer[i] = 0;
				yAvgBuffer[i] = 0;
			}
		}

		sf::Color *color;
		const unsigned short mouseHeight = 29;
		const unsigned short mouseWidth  = 23;

		unsigned int getXpos() {
			return this->xPos;
		}

		unsigned int getYpos() {
			return this->yPos;
		}

		void setXpos(int input) {
			if (input < 0) {
				input = 0;
			}
			else if (input > windowWidth) {
				input = windowWidth;
			}
			xPos = input;
		}

		void setYpos(int input) {
			if (input < 0) {
				input = 0;
			}
			else if (input > windowHeight) {
				input = windowHeight;
			}
			yPos = input;
		}

		void getInputX(int input) {
			xInputs.push(input);
		}

		void getInputY(int input) {
			yInputs.push(input);
		}

		void moveX(int input) {
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
			setRotation();
		}

		void moveY(int input) {
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
			setRotation();
		}

		sf::Vector2<float> getAverageMoves()
		{
			float sumX = 0;
			float sumY = 0;
			for (int i = 0; i < AVG_BUFFER_LEN; i++)
			{
				sumX += xAvgBuffer[i];
				sumY += yAvgBuffer[i];
			}

			return sf::Vector2<float>(sumX / AVG_BUFFER_LEN, sumY / AVG_BUFFER_LEN);
		}

		void setRotation()
		{
			sf::Vector2<float> averages = getAverageMoves();
			rotation = std::round(std::atan2(averages.y, averages.x) * 180 / PI) + 90;
			//printf("rotation: %i\n", rotation);
		}

		int update() {
			while (!xInputs.empty()) {
				moveX(xInputs.front());
				xInputs.pop();
			}

			while (!yInputs.empty()) {
				moveY(yInputs.front());
				yInputs.pop();
			}
			return 0;
		}

		void fireBasicBullet() {
			
		}

		void queueBasicBullet() {
			basicBulletQueued = true;
		}
};