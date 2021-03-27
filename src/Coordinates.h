#ifndef _COORDINATES
#define _COORDINATES


class Coordinates
{
public:
	void setCoordinates(int x, int y);
	float getDistance(Coordinates& c);
	float getAngle(Coordinates& c);
	void translate(Coordinates& c);

private:
	float x;
	float y;
	float angle;

	bool checkSpace(Coordinates& c);
}



#endif	//COORDINATES
