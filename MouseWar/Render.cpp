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

		/* TODO: draw all entities */
		for (int i = 0; i < game->numPlayers; i++) {
			window->draw(*(game->getCursor(i)));
		}
		window->display();

	}
}