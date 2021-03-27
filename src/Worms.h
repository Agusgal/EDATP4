#ifndef WORMS_H
#define WORMS_H


#include <allegro5/allegro.h>


class Worm
{
public:

	Worm();

	bool setSprite();
	void setState(int state);
	void setPosition(int x, int y);

private:
	int posX;
	int posY;
	int state;
	ALLEGRO_BITMAP* sprite;
};

#endif // !WORMS_H