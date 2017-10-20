#include "MouseWar.hpp"


int main()
{	
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	// Create window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(desktop.width, desktop.height, desktop.bitsPerPixel), "MOUSE WAR", sf::Style::None, settings);

	window.setMouseCursorVisible(false);
	window.setFramerateLimit(200);

	/* Initialize ManyMouse */
	int available_mice = initManyMouse();

	/* Instantiate game */
	std::shared_ptr<Game> game = std::make_shared<Game>();

	//TODO: CHANGE THIS LATER SO ITS ACTUALLY THE NUMBER OF ACTIVE PLAYERS, NOT JUST CONNECT MICE!! WOWEE
	game->numPlayers = available_mice;
	game->window = &window;

	std::vector<sf::Color> colors{ sf::Color::Blue,sf::Color::Red,sf::Color::Green,sf::Color::Black,sf::Color::Yellow,sf::Color::White,sf::Color::Cyan,sf::Color::Magenta };

	/* Create cursor objects for the game based on how many mice are plugged in */
	for	(int i = 0; i < available_mice; i++) {
		game->addCursor(std::make_shared<Cursor>(game, &colors.at(i)));
	}

	/* Deactivate the openGL context for the window before launching rendering thread */
	window.setActive(false);

	/* Launch the rendering thread */
	sf::Thread thread(&renderingThread, game);
	thread.launch();
	
	// Counter for total miliseconds elapsed
	std::chrono::milliseconds t(0);
	// Constant for time step (10 ms)
	const std::chrono::milliseconds dt(10);


	std::chrono::milliseconds currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::chrono::milliseconds accumulator(0);

	/*******************
	 * MAIN GAME LOOP
	 * *****************/
	while (window.isOpen()) {

		/* Handle SFML events. Right now, we only care if the window closes. */
		sf::Event sfevent;
		while (window.pollEvent(sfevent)) {
			if (sfevent.type == sf::Event::Closed) {
				window.close();
				game->clearCursors();
			}
		}

		/* Handle input from ManyMouse */
		processMouseEvents(game);

		//Calculates time since the last round of updates
		std::chrono::milliseconds newTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		std::chrono::milliseconds frameTime = newTime - currentTime;
		
		currentTime = newTime;
		accumulator += frameTime;

		// Consumes elapsed time since last update cycle in discrete time steps of 10ms
		while (accumulator >= dt)
		{
			/* Update game logic of each entity */
			game->update();
			accumulator -= dt;
			t += dt;
		}
	}

	ManyMouse_Quit();

	return 0;
}


/**
 * \brief Initialize the ManyMouse driver.
 * \return number of available mice, if there are mice available.
 *		   Otherwise, returns 0.
 */
int initManyMouse() {
	const int available_mice = ManyMouse_Init();

	if (available_mice < 0) {
		printf("Error initializing ManyMouse!\n");
		ManyMouse_Quit();
		return 0;
	}

	printf("ManyMouse driver: %s\n", ManyMouse_DriverName());

	if (available_mice == 0) {
		printf("No mice detected!\n");
		ManyMouse_Quit();
		return 0;
	}

	for (int i = 0; i < available_mice; i++) {
		printf("#%d: %s\n", i, ManyMouse_DeviceName(i));
	}

	printf("\n");
	return available_mice;
}


/**
* \brief Process all events in ManyMouse queue since the last time this function was called.
* \param game
* \return error code
*/
int processMouseEvents(std::shared_ptr<Game> game) {
	ManyMouseEvent event;

	while (ManyMouse_PollEvent(&event)) {
		/* Relative motion. This is normal for mouse movement. */
		if (event.type == MANYMOUSE_EVENT_RELMOTION) {
			//printf("Mouse #%u relative motion %s %d\n", event.device, event.item == 0 ? "X" : "Y", event.value);	
			/* X direction*/
			if (event.item == 0) {
				game->getCursor(event.device)->getInputX(event.value);
			}
			/* Y direction */
			else {
				game->getCursor(event.device)->getInputY(event.value);
			}
		}
		/* Absolute motion. Not really used so far. */
		else if (event.type == MANYMOUSE_EVENT_ABSMOTION) {
			//printf("Mouse #%u absolute motion %s %d\n", event.device, event.item == 0 ? "X" : "Y", event.value);
		}
		/* All button presses */
		else if (event.type == MANYMOUSE_EVENT_BUTTON) {
			//printf("Mouse #%u button %u %s\n", event.device, event.item, event.value ? "down" : "up");
		}
		/* Scroll wheel */
		else if (event.type == MANYMOUSE_EVENT_SCROLL) {
			const char *wheel;
			const char *direction;
			/* Vertical scroll */
			if (event.item == 0) {
				wheel = "vertical";
				direction = ((event.value > 0) ? "up" : "down");
			}
			/* Horizontal scroll */
			else {
				wheel = "horizontal";
				direction = ((event.value > 0) ? "right" : "left");
			}
			//printf("Mouse #%u wheel %s %s\n", event.device, wheel, direction);
		}
		/* Mouse has disconnected from the computer. */
		else if (event.type == MANYMOUSE_EVENT_DISCONNECT) {
			//printf("Mouse #%u disconnect\n", event.device);
		}
		/* Unhandled events */
		else {
			//printf("Mouse #%u unhandled event type %d\n", event.device, event.type);
		}
	}
	return 0;
}