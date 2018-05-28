#include "System.h"

void System::addEntity(MW_EntityID id, Entity* entity)
{
	entities.insert({ id, entity });
}