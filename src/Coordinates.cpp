#include <cmath>

#include "Coordinates.h"
#include "Config.h"


void Coordinates::setCoordinates(int x, int y);
{
	this->x = x;
	this->y = y;
}

void Coordinates::translate(Coordinates& c)
{


}

float Coordinates::getDistance(Coordinates& c) 
{
    return  (float) (sqrt(pow(c.x - x, 2) + pow((c.y - y), 2)));
}

float Coordinates::getAngle(Coordinates& c)
{

}

bool Coordinates::checkSpace()
{
	if(c.x>START_RING && c.x<FINISH_RING)
	{
		return false;
	}
	else 
	{
		return true;
	}
}
	