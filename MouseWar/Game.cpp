#include "Game.hpp"

int Game::addCursor(std::unique_ptr<Cursor> cursor) {
	cursors.push_back(std::move(cursor));
	return 0;
}

Cursor* Game::getCursor(int cursorNumber) {
	return cursors.at(cursorNumber).get();
}

void Game::clearCursors()
{
	cursors.clear();
}

/* Update the game logic by one tick.
 * This gets every entity in the game, and advances each of their states by one. */
int Game::update() {
	for (auto const& cursorPointer : cursors) {
		cursorPointer->update();
	}
	return 0;
}