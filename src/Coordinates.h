#ifndef _COORDINATES
#define _COORDINATES


class Coordinates
{
public:

	Coordinates();

	void setCoordinates(float x, float y);
	void setX(float x);
	void setY(float y);

	float getX(void);
	float getY(void);

	void translate(float offsetX, float offsetY = 0);

	bool checkSpaceX(void);
	void checkSpace(void);

private:
	float x;
	float y;
};



#endif	//COORDINATES
