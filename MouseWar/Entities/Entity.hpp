#pragma once

#include <memory>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "../MW_Common.h"
#include "../Components/TransformComponent.h"
#include "../Components/DrawComponent.h"



/* All "things" in MouseWar are entities. They have a position, and can be drawn. */
class Entity_old : public sf::Drawable {
public:
	/* Virtual destructor makes sure that subclass destructor is called */
	virtual ~Entity_old() {};

	/* It's possible that these don't have to be virtual. */
	virtual int getxPos() = 0;
	virtual int getyPos() = 0;
	virtual void setxPos(int input) = 0;
	virtual void setyPos(int input) = 0;

protected:
	int xPos = 0;
	int yPos = 0;

	/* Draw this entity to the render target */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};

/* All "things" in MouseWar are entities. They have a position, and can be drawn. */
class Entity
{
public:
	Entity(MW_ComponentField field);

	std::unique_ptr<TransformComponent> transform_c;
	std::unique_ptr<DrawComponent>      draw_c;
};