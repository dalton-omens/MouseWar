#include "System.h"

void System::addEntity(MW_EntityID id, Entity* entity)
{
	entities.insert({ id, entity });
}

void System::removeEntity(MW_EntityID id) {
	entities.erase(id);
}