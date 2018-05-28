#pragma once

#include "../MW_Common.h"
#include <memory>
#include <SFML/Graphics.hpp>

class DrawComponent {
public:
	DrawComponent();

	std::unique_ptr<sf::Drawable> shape;
};