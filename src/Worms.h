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
	void setPosition(int x, int y);

	float getPosition(int pos);

	void startMovingLeft(void);
	void startMovingRight(void);
	void startJumping(void);
	
	void stopMovingLeft(void);
	void stopMovingRight(void);
	void stopJumping(void);

	void update(void);

	ALLEGRO_BITMAP* getSprite(void);
	int getDirection(void);

private:
	Coordinates point;
	int state;
	int direction;
	int frameCount;
	ALLEGRO_BITMAP* sprite;
	ALLEGRO_PATH* path;

	void changeState(int newState);
	void walk(void);
	void jump(void);
};

#endif // !WORMS_H