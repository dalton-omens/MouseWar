#include "RenderSystem.h"

void RenderSystem::update()
{
	/* Iterate through all entities that belong to the rendering system and draw them 
	 * based on their drawing component. Entities must have a DrawComponent to be drawn
	 * to the render target.
	 */
	for (auto const pair : entities)
	{
		Entity *entity = pair.second;
		if (entity->draw_c)
		{
			window->draw(*entity->draw_c->shape);
		}
	}
}