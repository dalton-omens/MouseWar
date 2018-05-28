#pragma once

/* Header file for all systems in MouseWar. */

#include "../Entities/Entity.hpp"
#include "../MW_Common.h"
#include <unordered_map>

class System
{
public:
	void addEntity(MW_EntityID id, Entity* entity);
	virtual void update();

	/* Virtual destructor makes sure that subclass destructor is called */
	virtual ~System() {};

private:
	std::unordered_map<MW_EntityID, Entity*> entities;
};