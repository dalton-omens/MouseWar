#pragma once

/* All "things" in MouseWar are entities. They have a position, and that's about it. 
 * Drawable, Physical, etc. all inherit from Entity.
 */
class Entity {
public:
	/* Virtual destructor makes sure that subclass destructor is called */
	virtual ~Entity() {};

	virtual int getxPos() = 0;
	virtual int getyPos() = 0;
	virtual void setxPos(int input) = 0;
	virtual void setyPos(int input) = 0;

protected:
	int xPos = 0;
	int yPos = 0;
};