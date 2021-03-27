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
    this->frameCount = 0;
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

bool Simulation::getEvent(void)
{
    return al_get_next_event(queue, &ev);
}