#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Config.h"
#include "Worms.h"


class Simulation 
{
public:
	Simulation();
	
	bool initAll(void);
	bool isOver(void);
	bool getEvent(void);
	void dispatcher(void);
	void destroyAll();

private:
	int displayWidth;
	int displayHeight;
	int fps;

	bool running;
	//Capaz se puede hacer una lista
	Worm worm1;
	Worm worm2;

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_EVENT ev;
	ALLEGRO_TIMER* simTimer;
	ALLEGRO_BITMAP* background;

	bool initAllegro(void);
	bool initDisplay(void);
	bool initTimer(void);
	bool initEvents(void);
	bool loadBackground(void);

	void startMoving(void);
	void stopMoving(void);

	void refresh(void);
	void draw(void);

	void closeDisplay(void);

};


#endif // !SIMULATION_H
