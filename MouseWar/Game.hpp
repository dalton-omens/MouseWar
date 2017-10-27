#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Entities/Cursor.hpp"
#include "Entities/BasicBullet.hpp"

class Cursor; // find out why this is necessary
class BasicBullet;

class Game {
public:
	int numPlayers;
	sf::RenderWindow *window;

	int addCursor(std::unique_ptr<Cursor> cursor);
	Cursor* getCursor(int cursorID);
	void clearCursors();

	int addProjectile(std::unique_ptr<BasicBullet> projectile);
	BasicBullet* getProjectile(int projID);
	void removeProjectile(int projID);
	int numProjectiles() const;
	void clearProjectiles();

	int update();
private:
	std::vector<std::unique_ptr<Cursor>> cursors;
	std::vector<std::unique_ptr<BasicBullet>> projectiles;
};