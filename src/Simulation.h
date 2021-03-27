#ifndef SIMULATION_H
#define SIMULATION_h

#include <stdio.h>
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
	
	bool isOver(void);
	bool getEvent(void);
	void dispatcher(void);

private:
	int displayWidth;
	int displayHeight;
	int fps;
	int frameCount;

	bool running;
	//Capaz se puede hacer una lista
	Worm worm1;
	Worm worm2;

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_EVENT ev;
	ALLEGRO_TIMER* simTimer;

	bool initAllegro(void);
	bool initDisplay(void);
	bool initTimer(void);
	bool initEvents(void);
};



#endif // !SIMULATION_H
