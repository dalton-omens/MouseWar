#pragma once

/* Header for main. Put all includes here */

#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include "manymouse/manymouse.h"
#include "Game.hpp"
#include "Render.hpp"


int processMouseEvents(std::shared_ptr<Game> game);
int initManyMouse();