#pragma once

#include<memory>
#include<SFML/Graphics.hpp>

/* All "things" in MouseWar are entities. They have a position, and can be drawn. */
class Entity : public sf::Drawable {
public:
	/* Virtual destructor makes sure that subclass destructor is called */
	virtual ~Entity() {};

	/* It's possible that these don't have to be virtual. */
	virtual int getxPos() = 0;
	virtual int getyPos() = 0;
	virtual void setxPos(int input) = 0;
	virtual void setyPos(int input) = 0;

protected:
	int xPos = 0;
	int yPos = 0;
	std::unique_ptr<sf::Drawable> shape;

	/* Draw this entity to the render target */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};