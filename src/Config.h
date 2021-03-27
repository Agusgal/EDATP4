#ifndef CONFIG_H
#define CONFIG_H

#include "allegro5/allegro.h"
#include <stdio.h>
#include <iostream>
#include <string>

enum action {WALK, JUMP};
enum states {IDLE, START_MOVING_RIGHT, START_MOVING_LEFT, MOVE_RIGHT, MOVE_LEFT, STATES_N};



#define DISPLAY_WIDTH 1920
#define DISPLAY_HEIGHT 696
#define STAR_RING	701
#define FINISH_RING	1212
#define FPS 50



#define DEBUG 


std::string spritePath(int frameNum, int action);


#endif // !CONFIG_H
