#include "Simulation.h"


/**********************************************
SIMULATION
Constructor de la clase.

Recibe : void

Retorna: void

**********************************************/
Simulation::Simulation() 
{
	this->displayWidth = DISPLAY_WIDTH;
	this->displayHeight = DISPLAY_HEIGHT;

    this->display = NULL;
    this->queue = NULL;
    this->simTimer = NULL;
    this->background = NULL;
    this->running = true;
    this->ev = { 0 };
    this->fps = FPS;

    this->worm1 = Worm();
    this->worm2 = Worm();
}

/**********************************************
ISOVER

Funcion que mantiene corriendo la simulacion en un while adentro del main

Recibe : void

Retorna: bool, siendo true el indicador para que se termine la simulacion

**********************************************/
bool Simulation::isOver() 
{
	return !running;
}


/**********************************************
INITALLEGRO
Funcion que inicializa allegro

Recibe : void

Retorna: bool, siendo False el indicador de que las incializaciones fueron correctas

**********************************************/
bool Simulation::initAllegro()
{
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize allegro !\n");
        return true;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Failed to initialize primitives addon!\n");
        return true;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "Failed to initialize keyboard!\n");
        return true;
    }

    if (!al_install_mouse()) {
        fprintf(stderr, "Failed to initialize mouse!\n");
        return true;
    }

    if (!al_init_image_addon()) {
        fprintf(stderr, "Failed to initialize image addon!\n");
        return true;
    }

    return false;
}

/**********************************************
INITDISPLAY
Funcion que inicializa el display de allegro

Recibe : void

Retorna: bool, siendo False el indicador de que no se pudo crear el display

**********************************************/
bool Simulation::initDisplay()
{
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(displayWidth, displayHeight);
    if (!display) 
    {
        fprintf(stderr, "Failed to create display!\n");
        return true;
    }

    al_set_window_title(display, "WORMS");
    return false;
}

/**********************************************
INITTIMER
Funcion que inicializa el timer de allegro

Recibe : void

Retorna: bool, siendo False el indicador de que no se pudo crear el timer

**********************************************/
bool Simulation::initTimer()
{
    simTimer = al_create_timer(1 / fps);
    if (!simTimer)
    {
        fprintf(stderr, "Failed to create simulation Timer!\n");
        return true;
    }
    return false;
}


/**********************************************
INITEVENT
Funcion que inicializa los eventos de allegro

Recibe : void

Retorna: bool, siendo False el indicador de que no se pudo crear la cola

**********************************************/
bool Simulation::initEvents()
{
    queue = al_create_event_queue();

    if (!queue)
    {
        fprintf(stderr, "Failed to create event queue!\n");
        al_destroy_display(display);
        return true;
    }

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    al_register_event_source(queue, al_get_timer_event_source(simTimer));

    return false;
}

/**********************************************
INITALL|
Funcion que inicializa  todos los recursos de allegro usados, entre ellos se encuentra el dsipaly, los eventos, el timer y el bitmap

Recibe : void

Retorna: bool, siendo False el indicador de que las incializaciones fueron correctas

**********************************************/
bool Simulation::initAll(void)
{
    if (initAllegro())
    {
        return true;
    }

    if (initDisplay())
    {
        return true;
    }

    if (initTimer())
    {
        return true;
    }

    if (loadBackground())
    {
        return true;
    }

    if (initEvents())
    {
        return true;
    }

    al_start_timer(simTimer);
    std::string path = "res\\wwalking\\wwalk-F1.png";
    this->worm1.setSprite(path);
    this->worm2.setSprite(path);

    this->worm1.setPosition(START_POSITION_X2, START_POSITION_Y);
    this->worm2.setPosition(START_POSITION_X, START_POSITION_Y);

    return false;
}

/**********************************************
LOADBACKGROUND
Funcion que inicializa el bitmap

Recibe : void

Retorna: bool, siendo False el indicador de que le bitmap no se pudo cargar

**********************************************/
bool Simulation::loadBackground(void)
{
    background = al_load_bitmap("res\\Scenario.png");
    if (!background) {
        fprintf(stderr, "Failed to load background scenario bitmap!\n");
        return true;
    }
    return false;
}

/**********************************************
DISPATCHER
Funcion que administra los eventos, derivandolos a sus respectivas funciones

Recibe : void

Retorna: void

**********************************************/
void Simulation::dispatcher(void)
{
    switch (ev.type)
    {
    case ALLEGRO_EVENT_KEY_DOWN:
        this->startMoving();
        break;

    case ALLEGRO_EVENT_KEY_UP:
        this->stopMoving();
        break;

    case ALLEGRO_EVENT_TIMER:
        this->refresh();
        break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        running = false;
        break;
    default:
        break;
    }
}

/**********************************************
GETEVENT
Funcion que agarra el proximo evento de la cola de allegro

Recibe : void

Retorna: bool, siendo False el indicador de que no puedo tomar al proximo evento

*********************************************/
bool Simulation::getEvent(void)
{
    return al_get_next_event(queue, &ev);
}

/**********************************************
STARTMOVING
Funcion que dependiendo de la tecla precionada , realiza una accion(saltar, mover derecha o izquierda)

Recibe : void

Retorna: void

**********************************************/
void Simulation::startMoving(void)
{
    switch (ev.keyboard.keycode)
    {
    case ALLEGRO_KEY_D:
        worm1.startMovingRight();
        break;
    case ALLEGRO_KEY_A:
        worm1.startMovingLeft();
        break;
    case ALLEGRO_KEY_W:
        worm1.startJumping();
        break;
    case ALLEGRO_KEY_RIGHT:
        worm2.startMovingRight();
        break;
    case ALLEGRO_KEY_LEFT:
        worm2.startMovingLeft();
        break;
    case ALLEGRO_KEY_UP:
        worm2.startJumping();
        break;

    default:
        break;
    }
}


void Simulation::stopMoving(void)
{
    switch (ev.keyboard.keycode)
    {
    case ALLEGRO_KEY_D:
        worm1.stopMovingRight();
        break;
    case ALLEGRO_KEY_A:
        worm1.stopMovingLeft();
        break;
    case ALLEGRO_KEY_W:
        worm1.stopJumping();
        break;
    case ALLEGRO_KEY_RIGHT:
        worm2.stopMovingRight();
        break;
    case ALLEGRO_KEY_LEFT:
        worm2.stopMovingLeft();
        break;
    case ALLEGRO_KEY_UP:
        worm2.stopJumping();
        break;

    default:
        break;
    }
}


void Simulation::refresh(void)
{
    worm1.update();
    worm2.update();
    this->draw(); 
    al_flip_display();
}

/**********************************************
DRAW
Funcion que dibuja el bitmap y los sprite de los worms

Recibe : void

Retorna: void

**********************************************/
void Simulation::draw(void)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(background, 0, 0, 0);

    al_draw_bitmap(worm1.getSprite(), worm1.getPosition(POS_X), worm1.getPosition(POS_Y), worm1.getDirection());//get direction funciona porque el flag de allegro para flipear es igual a nuestro define de direccion
    al_draw_bitmap(worm2.getSprite(), worm2.getPosition(POS_X), worm2.getPosition(POS_Y), worm2.getDirection());
}

/**********************************************
DESTROY
Funcion que destruye todos los recursos relacionados con allegro

Recibe : void

Retorna: void

**********************************************/
void Simulation:: destroyAll()
{
    al_destroy_bitmap(background);
    al_destroy_bitmap(worm1.getSprite());
    al_destroy_bitmap(worm2.getSprite());
    
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(simTimer);
    
}
