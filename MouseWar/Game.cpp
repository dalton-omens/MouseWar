#include "Game.hpp"

/* Add a cursor to the Game, and transfer ownership of the pointer. */
int Game::addCursor(std::unique_ptr<Cursor> cursor) {
	cursors.push_back(std::move(cursor));
	return 0;
}

Cursor* Game::getCursor(int cursorID) {
	return cursors.at(cursorID).get();
}

void Game::clearCursors()
{
	cursors.clear();
}

/* Add a projectile to the Game, and transfer ownership of the pointer. */
int Game::addProjectile(std::unique_ptr<BasicBullet> projectile) {
	projectiles.push_back(std::move(projectile));
	return 0;
}

BasicBullet* Game::getProjectile(int projID) {
	return projectiles.at(projID).get();
}

/* Remove a projectile from the projectiles vector. */
void Game::removeProjectile(int projID) {
	projectiles.erase(projectiles.begin() + projID);
}


int Game::numProjectiles() const {
	return projectiles.size();
}

void Game::clearProjectiles() {
	projectiles.clear();
}


/* Update the game logic by one tick.
 * This gets every entity in the game, and advances each of their states by one. */
int Game::update() {
	for (auto const& cursorPointer : cursors) {
		cursorPointer->update();
	}
	for (auto const& projPointer : projectiles) {
		projPointer->update();
	}
	return 0;
}