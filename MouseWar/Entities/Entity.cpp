#include "Entity.hpp"

Entity::Entity(MW_ComponentField field) :
	transform_c(nullptr),
	draw_c(nullptr)
{
	/* Initialize only components indicated in the bitfield. */
	if (field & TRANSFORM_COMPONENT) transform_c = std::make_unique<TransformComponent>();
	if (field & DRAW_COMPONENT) draw_c = std::make_unique<DrawComponent>();
}