#ifndef WORMS_H
#define WORMS_H

#include <allegro5/allegro.h>
#include "Coordinates.h"
#include "Config.h"

class Worm
{
public:

	Worm();

	bool setSprite(std::string sprite);
	void setState(int state);
	void setPosition(int x, int y);

	void startMovingLeft(void);
	void startMovingRight(void);
	void startJumping(void);
	void update(void);

	ALLEGRO_BITMAP* getSprite(void);

private:
	Coordinates point;
	int state;
	int direction;
	int frameCount;
	ALLEGRO_BITMAP* sprite;


	void walk(void);
	void jump(void);
};

#endif // !WORMS_H