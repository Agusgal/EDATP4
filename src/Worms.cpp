#include "Worms.h"
using namespace std;

/**********************************************
WORM
constructor de la clase worm

Recibe : void

Retorna: void

**********************************************/
Worm::Worm()
{
	point = Coordinates();
	state = IDLE;
	direction = LEFT;
	sprite = NULL;
	frameCount = 0;
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


float Worm::getPosition(int pos)
{
	if (pos == POS_X)
	{
		return this->point.getX();
	}
	else
	{
		return this->point.getY();
	}
}

/**********************************************
GETSPRITE
retorna sprite de allegro

Recibe : void

Retorna: sprite de allegro (bitmap)

**********************************************/
ALLEGRO_BITMAP* Worm::getSprite(void)
{
	return this->sprite;
}


int Worm::getDirection(void)
{
	return this->direction;
}

/**********************************************
CHANGESTATE
cambia al estado ingresado

Recibe : nuevo estado

Retorna: void

**********************************************/
void Worm::changeState(int newState)
{
	this->state = newState;
}

/**********************************************
STARTMOVINGLEFT
Funcion que actualiza el estado y la direccion del worm(izquierda)

Recibe : void

Retorna: void

**********************************************/
void Worm::startMovingLeft(void)
{
	if (state == IDLE)
	{
		this->changeState(START_MOVING_LEFT);
		direction = LEFT;
	}
}

/**********************************************
STARTMOVINGRIGHT
Funcion que actualiza el estado y la direccion del worm(derecha)

Recibe : void

Retorna: void

**********************************************/
void Worm::startMovingRight(void)
{
	if (state == IDLE)
	{
		this->changeState(START_MOVING_RIGHT);
		direction = RIGHT;
	}
}

/**********************************************
STOPMOVINGLEFT
Se ejcuta cuando se deja de rpesionar una tecla, dependiendo del estado actual cambia al proximo estado correspondiente

Recibe : void

Retorna: void

**********************************************/
void Worm::stopMovingLeft(void)
{
	if (state == START_MOVING_LEFT)
	{
		//frameCount = 0;
		this->changeState(IDLE);
	}
	else if (state == MOVE_LEFT)
	{
		this->changeState(STOP_MOVING_LEFT);
	}
}

/**********************************************
STOPMOVINGRIGHT
Se ejcuta cuando se deja de rpesionar una tecla, dependiendo del estado actual cambia al proximo estado correspondiente

Recibe : void

Retorna: void

**********************************************/
void Worm::stopMovingRight(void)
{
	if (state == START_MOVING_RIGHT)
	{
		//frameCount = 0;
		this->changeState(IDLE);
	}
	else if (state == MOVE_RIGHT)
	{
		this->changeState(STOP_MOVING_RIGHT);
	}
}

/**********************************************
STARTJUMPING
Funcion que actualiza el estado (salto)

Recibe : void

Retorna: void

**********************************************/
void Worm::startJumping(void)
{
	if (state == IDLE)
	{
		this->changeState(START_JUMPING);
	}
}

void Worm::stopJumping(void)
{
	if (state == START_JUMPING)
	{
		this->changeState(IDLE);
	}
	else if (state == MOVE_JUMP)
	{
		this->changeState(STOP_JUMPING);
	}
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
		if (frameCount < 5)
		{
			frameCount++;
		}
		else
		{
			this->changeState(MOVE_LEFT);
		}
		break;
	case START_MOVING_RIGHT:
		if (frameCount < 5)
		{
			frameCount++;
		}
		else
		{
			this->changeState(MOVE_RIGHT);
		}
		break;
	
	case STOP_MOVING_LEFT:
	case MOVE_LEFT:
		if (frameCount < 22)
		{
			frameCount++;
			if (frameCount > 16 && frameCount != 22)
			{
				setSprite(spritePath(frameCount - 5 - 1, WALK));
			}
			else if(frameCount <= 16)
			{
				setSprite(spritePath(frameCount - 5, WALK));
			}

			if (frameCount == 22)
			{
				setSprite(spritePath(4, WALK));
				walk();
			}
		}
		else if (frameCount < 36)
		{
			frameCount++;
			if (frameCount > 31 && frameCount != 36)
			{
				setSprite(spritePath(frameCount - 19 - 1, WALK));
			}
			else if (frameCount <= 31)
			{
				setSprite(spritePath(frameCount - 19, WALK));
			}
			
			if (frameCount == 36)
			{
				setSprite(spritePath(4, WALK));
				walk();
			}
		}
		else if (frameCount < 50)
		{
			frameCount++;
			if (frameCount > 44 && frameCount != 50)
			{
				setSprite(spritePath(frameCount - 33 - 1, WALK));
			}
			else if (frameCount <= 44)
			{
				setSprite(spritePath(frameCount - 33, WALK));
			}
			
			if (frameCount == 50)
			{
				setSprite(spritePath(4, WALK));
				walk();
				frameCount = 0;
				if (state == MOVE_LEFT)
				{
					this->changeState(START_MOVING_LEFT);
				}
				else
				{
					this->changeState(IDLE);
				}
			}
		}
		break;

	case STOP_MOVING_RIGHT:	
	case MOVE_RIGHT:
		if (frameCount < 22)
		{
			frameCount++;

			if (frameCount > 16 && frameCount != 22)
			{
				setSprite(spritePath(frameCount - 5 - 1, WALK));
			}
			else if (frameCount <= 16)
			{
				setSprite(spritePath(frameCount - 5, WALK));
			}
			
			if (frameCount == 22)
			{
				setSprite(spritePath(4, WALK));
				walk();
			}
		}
		else if (frameCount < 36)
		{
			frameCount++;
			if (frameCount > 31 && frameCount != 36)
			{
				setSprite(spritePath(frameCount - 19 - 1, WALK));
			}
			else if (frameCount <= 31)
			{
				setSprite(spritePath(frameCount - 19, WALK));
			}

			if (frameCount == 36)
			{
				setSprite(spritePath(4, WALK));
				walk();
			}
		}
		else if (frameCount < 50)
		{
			frameCount++;
			if (frameCount > 44 && frameCount != 50)
			{
				setSprite(spritePath(frameCount - 33 - 1, WALK));
			}
			else if (frameCount <= 44)
			{
				setSprite(spritePath(frameCount - 33, WALK));
			}
			
			if (frameCount == 50)
			{
				setSprite(spritePath(4, WALK));
				walk();
				frameCount = 0;
				if (state == MOVE_RIGHT)
				{
					this->changeState(START_MOVING_RIGHT);
				}
				else
				{
					this->changeState(IDLE);
				}
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
			this->changeState(MOVE_JUMP);
		}
		break;
	
	case STOP_JUMPING:
	case MOVE_JUMP:
		if (frameCount < 9)
		{
			frameCount++;
			setSprite(spritePath(frameCount - 5, JUMP));
		}
		else if (frameCount < 9 + JUMP_DURATION)
		{
			frameCount++;
			setSprite(spritePath(5, JUMP));
			this->jump();
		}
		else if (frameCount < 9 + JUMP_DURATION + 6)
		{
			frameCount++;
			if (frameCount == 9 + JUMP_DURATION + 6)
			{
				setSprite(spritePath(1, JUMP));
				//capaz falta un jump aca
				frameCount = 0;
				if (state == MOVE_JUMP)
				{
					this->changeState(START_JUMPING);
				}
				else
				{
					this->changeState(IDLE);
				}
			}
			else
			{
				setSprite(spritePath(frameCount - JUMP_DURATION - 4, JUMP));
			}
		}
		break;
	
	case IDLE:
		{
			frameCount = 0;
		}
		break;
	
	default:
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
JUMP
Funcion que hace  saltar a los worms frame a frame.es

Recibe : void

Retorna: void

**********************************************/
void Worm::jump(void)
{
	float stepX = STEP_X_JUMP; //El step esta definido en Config.h.
	float stepY = SPEED * sin(ANGLE) * (frameCount - 9) -  0.5 * GRAVITY * powf((frameCount - 9), 2);// -0.5 * GRAVITY * powf((frameCount - 9), 2);	//Ecuacion caida libre.
	
	float previousStepY = SPEED * sin(ANGLE) * (frameCount - 1 - 9) - 0.5 * GRAVITY * powf((frameCount - 1 - 9), 2);

	float step = stepY - previousStepY;

	if (direction == LEFT)	//En caso de moverse hacia la izquierda, se modifica sentido.
	{
		stepX *= -1;
	}

	point.translate(stepX, -step);	//Se traslada gusano
	point.checkSpace();	//Y en caso que el desplazamiento exceda el area, se lo mantiene dentro del ring.
}