#include <iostream>

#include "Simulation.h"

using namespace std;

int main(void) 
{
	Simulation sim;
	
	//Init all
	while (!sim.isOver())
	{
		if (sim.getEvent())
		{
		
			//dispatcher con evento guardado en ev. 
		}
	
	}
	//destroy

	return 0;
}