#pragma once

#include "System.h"
#include "SFML/Graphics.hpp"

class RenderSystem : public System
{
public:
	void update() override;

private:
	std::unique_ptr<sf::RenderWindow> window;
};