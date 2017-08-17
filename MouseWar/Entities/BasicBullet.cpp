#include <SFML/Graphics.hpp>

#define BULLET_RADIUS 100
#define BULLET_POINT_COUNT 20

class BasicBullet {

	private:
		int xPos, yPos;
		double vel, rotation;

	public:
		BasicBullet(int xPos, int yPos, double vel, double rotation) {
			this->xPos = xPos;
			this->yPos = yPos;
			this->vel = vel;
			this->rotation = rotation;
		}

		sf::CircleShape draw() {
			sf::CircleShape bullet(BULLET_RADIUS, BULLET_POINT_COUNT);
			bullet.setFillColor(sf::Color::Black);
			bullet.setPosition(xPos, yPos);
			return bullet;
		}


};