#include <iostream>

#include "Simulation.h"

using namespace std;

int main(void) 
{
	Simulation sim;
	
	sim.initAll();
	while (!sim.isOver())
	{
		if (sim.getEvent())
		{
			sim.dispatcher();
		}
	}
	sim.destroyAll();

	return 0;
}