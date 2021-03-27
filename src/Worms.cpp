#include "Worms.h"

Worm::Worm()
{
	this->posX = 0;
	this->posY = 0;
	this->state = IDLE;
	this->sprite = NULL;
	this->frameCount = 0;
}

void Worm::setState(int state)
{
	this->state = state;
}

void Worm::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}

bool Worm::setSprite(std::string path)
{
	sprite = al_load_bitmap(path.c_str());
	if (!sprite) 
	{
		fprintf(stderr, "Failed to create animation bitmap!\n");
		return true;
	}
	return false;
}


void Worm::startMovingLeft(void)
{
	if (state == IDLE)
	{
		
	
	}
	
	state = START_MOVING_LEFT;
}

void Worm::startMovingRight(void)
{
	//Things
}

void Worm::update(void)
{
	switch (state)
	{
	case START_MOVING_LEFT:
		if (frameCount < 5)
		{
			frameCount++;
		}
		else
		{
			state = MOVE_LEFT;
		}
		break;

	case MOVE_LEFT: 
		if (frameCount < 19)
		{
			setSprite(spritePath(frameCount - 5, WALK));
			frameCount++;
		}
		else if (frameCount < 33)
		{
			walk(STEP);
			setSprite(spritePath(frameCount - 19, WALK));
			frameCount++;
		}
		else if (frameCount < 50)
		{
			walk(STEP);
			setSprite(spritePath(frameCount - 33, WALK));
			frameCount++;
		}
		else:
		{
			walk(STEP);
			state = START_MOVING_LEFT;
			frameCount = 0;
		}
		break;
	}	


}