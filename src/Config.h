#ifndef CONFIG_H
#define CONFIG_H

#include "allegro5/allegro.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>

enum pos {POS_X, POS_Y};
enum action {WALK, JUMP};
enum states {IDLE, START_MOVING_RIGHT, START_MOVING_LEFT, START_JUMPING, MOVE_RIGHT, MOVE_LEFT, MOVE_JUMP, STOP_MOVING_RIGHT, STOP_MOVING_LEFT, STOP_JUMPING, STATES_N};
enum directions {LEFT, RIGHT};


#define DISPLAY_WIDTH     1920
#define DISPLAY_HEIGHT    696
#define START_RING	      701
#define FINISH_RING	      1212
#define FPS               50

#define START_POSITION_X	955
#define START_POSITION_X2	800
#define START_POSITION_Y	616

#define STEP_RIGHT_LEFT		9
#define STEP_X_JUMP			2.25

#define WORM_WIDTH	60

#define SPEED		4.5
#define GRAVITY		0.24
#define ANGLE		1.047197551

#define JUMP_DURATION std::ceil((2 * SPEED * std::sin(ANGLE)) / (GRAVITY))

#define DEBUG


std::string spritePath(int frameNum, int action);

#endif // !CONFIG_H