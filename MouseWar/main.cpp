#include "MouseWar.hpp"


/**
 * \brief Process all events in queue since the last time this function was called.
 * \param game 
 * \return error code
 */
int processMouseEvents(std::shared_ptr<Game> game) {
	ManyMouseEvent event;
	
	while (ManyMouse_PollEvent(&event))
	{
		if (event.type == MANYMOUSE_EVENT_RELMOTION)
		{
				//printf("Mouse #%u relative motion %s %d\n", event.device, event.item == 0 ? "X" : "Y", event.value);

				if (event.item == 0) {
					game->getCursor(event.device)->getInputX(event.value);
				}
				else {
					game->getCursor(event.device)->getInputY(event.value);
				}

		}

		else if (event.type == MANYMOUSE_EVENT_ABSMOTION)
		{
				//printf("Mouse #%u absolute motion %s %d\n", event.device, event.item == 0 ? "X" : "Y", event.value);
		}

		else if (event.type == MANYMOUSE_EVENT_BUTTON)
		{
				//printf("Mouse #%u button %u %s\n", event.device, event.item, event.value ? "down" : "up");
		}

		else if (event.type == MANYMOUSE_EVENT_SCROLL)
		{
			const char *wheel;
			const char *direction;
			if (event.item == 0)
			{
				wheel = "vertical";
				direction = ((event.value > 0) ? "up" : "down");
			}
			else
			{
				wheel = "horizontal";
				direction = ((event.value > 0) ? "right" : "left");
			}
				//printf("Mouse #%u wheel %s %s\n", event.device, wheel, direction);
		}

		else if (event.type == MANYMOUSE_EVENT_DISCONNECT) {
				//printf("Mouse #%u disconnect\n", event.device);
		}
		else
		{
				//printf("Mouse #%u unhandled event type %d\n", event.device, event.type);
		}
	}
	return 0;
}


/**
 * \brief Rendering thread. game parameter should not be modified.
 * \param game 
 */
void renderingThread(std::shared_ptr<Game> game)
{
	sf::RenderWindow *window = game->window;

    // the rendering loop
	while (window->isOpen())
	{

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

			cursor.setRotation(game->getCursor(i)->rotation);

			cursor.setFillColor(*(game->getCursor(i)->color));
			//printf("Mouse 0 x position %i\n", game->getCursor(0).getXpos());
			//printf("Mouse 0 y position %i\n", game->getCursor(0).getYpos());


			cursor.setPosition(game->getCursor(i)->getXpos(), game->getCursor(i)->getYpos());
			window->draw(cursor);
		}
		window->display();
	
    }
}


int main()
{
	
	const int available_mice = ManyMouse_Init();
	

	if (available_mice < 0)
	{
		printf("Error initializing ManyMouse!\n");
		ManyMouse_Quit();
		return 2;
	}

	printf("ManyMouse driver: %s\n", ManyMouse_DriverName());

	if (available_mice == 0)
	{
		printf("No mice detected!\n");
		ManyMouse_Quit();
		return 1;
	}

	for (int i = 0; i < available_mice; i++) {
		printf("#%d: %s\n", i, ManyMouse_DeviceName(i));
	}

	printf("\n");

	
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	// Create window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(desktop.width, desktop.height, desktop.bitsPerPixel), "MOUSE WAR", sf::Style::None, settings);

	window.setMouseCursorVisible(false);
	window.setFramerateLimit(200);

	//make the game! wowee
	std::shared_ptr<Game> game = std::make_shared<Game>();

	//TODO: CHANGE THIS LATER SO ITS ACTUALLY THE NUMBER OF ACTIVE PLAYERS, NOT JUST CONNECT MICE!! WOWEE
	game->numPlayers = available_mice;
	
	game->window = &window;

	std::vector<sf::Color> colors{ sf::Color::Blue,sf::Color::Red,sf::Color::Green,sf::Color::Black,sf::Color::Yellow,sf::Color::White,sf::Color::Cyan,sf::Color::Magenta };

	for	(int i = 0; i < available_mice; i++) {
		game->addCursor(std::make_shared<Cursor>(game, &colors.at(i)));
	}
	// deactivate its OpenGL context
	window.setActive(false);

	// launch the rendering thread
	sf::Thread thread(&renderingThread, game);
	thread.launch();
	
	// Counter for total miliseconds elapsed
	std::chrono::milliseconds t(0);
	// Constant for time step (10 ms)
	const std::chrono::milliseconds dt(10);


	std::chrono::milliseconds currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::chrono::milliseconds accumulator(0);

	while (window.isOpen()) {
		sf::Event sfevent;
		while (window.pollEvent(sfevent))
		{
			if (sfevent.type == sf::Event::Closed)
			{
				window.close();

				game->clearCursors();
			}
		}

		processMouseEvents(game);

		//Calculates time since the last round of updates
		std::chrono::milliseconds newTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		std::chrono::milliseconds frameTime = newTime - currentTime;
		
		currentTime = newTime;

		accumulator += frameTime;

		// Consumes elapsed time since last update cycle in discrete time steps of 10ms
		while (accumulator >= dt)
		{
			// Update game logic of each entity
			game->update();
			accumulator -= dt;
			t += dt;
		}
		

	}

	return 0;
}