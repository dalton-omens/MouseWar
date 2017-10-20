#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Drawable : Entity {
public:
	/* Virtual destructor makes sure that subclass destructor is called */
	virtual ~Drawable() {};

	virtual sf::Drawable* draw() = 0;

protected:
	int xPos = 0; // unsure why I have to re-declare these; declared in Entity
	int yPos = 0;
	std::unique_ptr<sf::Drawable> shape;
};