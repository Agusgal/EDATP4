#include "Worms.h"

#include <cmath>

/**********************************************
WORM
constructor de la clase worm

Recibe : void

Retorna: void

**********************************************/
Worm::Worm()
{
	point = Coordinates();
	state = 0;
	direction = LEFT;
	sprite = NULL;
	frameCount = 0;
}


/**********************************************
SETESTATE
Funcion que configura el estado del worm

Recibe : int con la informacion del estado

Retorna: void

**********************************************/
void Worm::setState(int state)
{
	this->state = state;
}


void Worm::setPosition(int x, int y)
{
	point.setCoordinates(x, y);
}

/**********************************************
SETSPRITE
Funcion que carga el sprite correspondiente en el worm

Recibe : string, que contiene la ruta del sprite

Retorna: bool, siendo False el indicador de que se cargo correctamente

**********************************************/
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

/**********************************************
STARTMOVINGLEFT
Funcion que actualiza el estado y la direccion del worm(izquierda)

Recibe : void

Retorna: void

**********************************************/
void Worm::startMovingLeft(void)
{
	state = START_MOVING_LEFT;
	direction = LEFT;
}

/**********************************************
STARTMOVINGRIGHT
Funcion que actualiza el estado y la direccion del worm(derecha)

Recibe : void

Retorna: void

**********************************************/
void Worm::startMovingRight(void)
{
	state = START_MOVING_RIGHT;
	direction = RIGHT;
}

//
//void Worm::startMovingLeft(void)
//{
//	state = START_MOVING_LEFT;
//}

/**********************************************
STARTJUMPING
Funcion que actualiza el estado (salto)

Recibe : void

Retorna: void

**********************************************/
void Worm::startJumping(void)
{
	state = START_JUMPING;
}

/**********************************************
UPDATE
Funcion que comprueba los estados de los worms , para que pueda controlar sus frame y de esta manera podamos movernos
Recibe : void

Retorna: void

**********************************************/
void Worm::update(void)
{
	switch (state)
	{
	case START_MOVING_LEFT:
	case START_MOVING_RIGHT:
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
	case MOVE_RIGHT:
		if (frameCount < 19)
		{
			frameCount++;
			setSprite(spritePath(frameCount - 5, WALK));
			if (frameCount == 19)
			{
				walk();
			}
		}
		else if (frameCount < 33)
		{
			frameCount++;
			setSprite(spritePath(frameCount - 19, WALK));
			if (frameCount == 33)
			{
				walk();
			}
		}
		else if (frameCount < 50)
		{
			frameCount++;
			setSprite(spritePath(frameCount - 33, WALK));
			if (frameCount == 50)
			{
				walk();
			}
		}
		break;
	case START_JUMPING:
		if (frameCount < 5)
		{
			frameCount++;
		}
		else
		{
			state = JUMP;
		}
		break;
	case MOVE_JUMP:
		if (frameCount < 15)
		{
			frameCount++;
			setSprite(spritePath(frameCount - 5, JUMP));
		}
		else if (frameCount < 50)
		{
			if (frameCount == 15)
			{
				setSprite(spritePath(1, JUMP));
			}
			frameCount++;
			jump();
		}
		break;
	default:
		{
			state = IDLE;
			frameCount = 0;
		}
		break;
	}	
}

/**********************************************
WALK
Funcion que mueve worm a la izquierda o derecha en step pixeles

Recibe : void

Retorna: void

**********************************************/
void Worm::walk(void)
{
	float step = STEP_RIGHT_LEFT;	//El step esta definido en Config.h.
	if (direction == LEFT)		//En caso de moverse hacia la izquierda, se modifica sentido.
	{
		step *= -1;
	}
	point.translate(step);
	point.checkSpace();
	
}

/**********************************************
WALK
Funcion que hace  saltar a los worms frame a frame.es

Recibe : void

Retorna: void

**********************************************/
void Worm::jump(void)
{
	float stepX = STEP_X_JUMP;	//El step en x esta definido en Config.h.
	float stepY = point.getY() + SPEED * sin(ANGLE) * (1 / FPS) - 0.5 * GRAVITY * powf((1 / FPS), 2);	//Ecuacion tiro parabolico por frame
	if (direction == LEFT)	//En caso de moverse hacia la izquierda, se modifica sentido.
	{
		stepX *= -1;
	}
	if (point.getX() == 0 && point.getY() != 0)	//Caso de bordes, pasa a ser caida libre
	{
		stepY -= SPEED * sin(ANGLE) * (1 / FPS);
	}
	point.translate(stepX, stepY);
	point.checkSpace();
}