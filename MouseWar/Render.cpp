#include "Render.hpp"

/**
* \brief Rendering thread. game parameter should not be modified.
* \param game
*/
void renderingThread(std::shared_ptr<Game> game) {
	sf::RenderWindow *window = game->window;

	/*** RENDERING LOOP ***/
	while (window->isOpen()) {

		/* Sets background */
		window->clear(sf::Color::White);

		for (int i = 0; i < game->numPlayers; i++) {

			sf::ConvexShape cursor(10);
			cursor.setPointCount(7);
			cursor.setPoint(0, sf::Vector2f(0, 0));
			cursor.setPoint(1, sf::Vector2f(11, 21));
			cursor.setPoint(2, sf::Vector2f(3, 18));
			cursor.setPoint(3, sf::Vector2f(3, 29));
			cursor.setPoint(4, sf::Vector2f(-3, 29));
			cursor.setPoint(5, sf::Vector2f(-3, 18));
			cursor.setPoint(6, sf::Vector2f(-11, 21));

			cursor.setRotation(game->getCursor(i)->getRotation());

			cursor.setFillColor(*(game->getCursor(i)->color));
			//printf("Mouse 0 x position %i\n", game->getCursor(0).getXpos());
			//printf("Mouse 0 y position %i\n", game->getCursor(0).getYpos());


			cursor.setPosition(game->getCursor(i)->getxPos(), game->getCursor(i)->getyPos());
			window->draw(cursor);
		}
		window->display();

	}
}