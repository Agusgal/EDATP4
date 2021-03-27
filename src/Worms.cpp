#include "Worms.h"

Worm::Worm()
{
	this->posX = 0;
	this->posY = 0;
	this->state = 0;
	this->sprite = NULL;
}

void Worm::setState(int state)
{
	this->state = state;
}

void Worm::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}