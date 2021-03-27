#ifndef WORMS_H
#define WORMS_H



#include <allegro5/allegro.h>


class Worm
{
public:

	Worm()
	{
		this->posX = 0;
		this->posY = 0;
		this->state = 0;
		this->sprite = NULL;
	}

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