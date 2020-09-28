#include "Fuel.h"
#include <include\math.h>

Fuel::Fuel()
{
}


Fuel::~Fuel()
{
}

Fuel::Fuel(float aangle)
{
	angle = aangle;
	count = 0;
	nEl = rand() % 7 + 1;
	height = (float)((rand() % 200 + 100) / 100);
	for (int i = 0; i < nEl; i++) {
		moveAngle.push_back(0);
	}
}



