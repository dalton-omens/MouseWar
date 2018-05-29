#pragma once

/* Header file for all systems in MouseWar. */

#include "../Entities/Entity.hpp"
#include "../MW_Common.h"
#include <unordered_map>

class System
{
public:
	void addEntity(MW_EntityID id, Entity* entity);
	void removeEntity(MW_EntityID id);
	virtual void update();

	/* Virtual destructor makes sure that subclass destructor is called */
	virtual ~System() {};

protected:
	std::unordered_map<MW_EntityID, Entity*> entities;
};