#include "Simulation.h"

Simulation::Simulation() 
{
	this->displayWidth = DISPLAY_WIDTH;
	this->displayHeight = DISPLAY_HEIGHT;

    this->display = NULL;
    this->queue = NULL;
    this->simTimer = NULL;
    this->running = true;
    this->ev = { 0 };
    this->fps = FPS;
}

bool Simulation::isOver() 
{
	return !running;
}

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

bool Simulation::initTimer()
{
    simTimer = al_create_timer(1 / fps);
    if (!simTimer)
    {
        fprintf(stderr, "Failed to create Timer!\n");
        return true;
    }
    return false;
}

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

bool Simulation::initAll(void)
{
    if (!initAllegro())
    {
        return true;
    }

    if (!initDisplay())
    {
        return true;
    }

    if (!initEvents())
    {
        return true;
    }

    if (!initTimer())
    {
        return true;
    }

    if (!loadBackground())
    {
        return true;
    }

    return false;
}


bool Simulation::loadBackground(void)
{
    background = al_load_bitmap("res\\Scenario.jpg");
    if (!background) {
        fprintf(stderr, "Failed to load background scenario bitmap!\n");
        return true;
    }
    return false;
}


bool Simulation::getEvent(void)
{
    return al_get_next_event(queue, &ev);
}

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
        //worm1.startJumping();
        break;
    case ALLEGRO_KEY_RIGHT:
        worm2.startMovingRight();
        break;
    case ALLEGRO_KEY_LEFT:
        worm2.startMovingLeft();
        break;
    case ALLEGRO_KEY_UP:
        //worm2.starJumping();
        break;

    default:
        break;
    }
    

}

void Simulation::dispatcher(void)
{
    switch(ev.type)
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

void Simulation::refresh(void)
{
    worm1.update();
    worm2.update();
    this->draw(); 
    //flip display
}

void Simulation::draw(void)
{
    al_draw_bitmap(background, 0, 0, 0);//falta cargasr los sprites
    
    al_draw_bitmap(worm1.getSprite(), );//faltan coordenadas en x, y
    al_draw_bitmap(worm2.getSprite(), );//faltan coordenadas en x, y


}

void Simulation:: destroyAll()
{
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(simTimer);
    al_destroy_bitmap(background);
    al_destroy_bitmap(worm1.getSprite());
    al_destroy_bitmap(worm2.getSprite());
}