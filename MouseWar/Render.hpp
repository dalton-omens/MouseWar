#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Game.hpp"

/**
* \brief Rendering thread. game parameter should not be modified.
* \param game
*/
void renderingThread(std::shared_ptr<Game> game);