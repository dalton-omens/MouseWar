#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Entities/Cursor.cpp"

class Game {
public:
	int numPlayers;
	sf::RenderWindow *window;

	int addCursor(std::shared_ptr<Cursor> cursor);
	std::shared_ptr<Cursor> getCursor(int cursorNumber);
	void clearCursors();
	int update();

private:
	std::vector<std::shared_ptr<Cursor>> cursors;
};