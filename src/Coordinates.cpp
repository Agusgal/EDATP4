#include <cmath>

#include "Coordinates.h"
#include "Config.h"



Coordinates::Coordinates()
{
	x = START_POSITION_X;
	y = START_POSITION_Y;
}

void Coordinates::setCoordinates(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Coordinates::setX(float x)
{
	this->x = x;
}

void Coordinates::setY(float y)
{
	this->y = y;
}

float Coordinates::getX(void)
{
	return x;
}

float Coordinates::getY(void)
{
	return y;
}

void Coordinates::translate(float offsetX, float offsetY)
{
	x += offsetX;
	y += offsetY;
}

bool Coordinates::checkSpaceX(void)
{
	return ((x > START_RING) && (x + WORM_WIDTH < FINISH_RING));
}

void Coordinates::checkSpace(void)
{
	if (x < START_RING)
	{
		x = START_RING;
	}
	else if (x + WORM_WIDTH > FINISH_RING)
	{
		x = FINISH_RING - WORM_WIDTH;
	}
	
	if (y > START_POSITION_Y)
	{
		y = START_POSITION_Y;
	}
}

