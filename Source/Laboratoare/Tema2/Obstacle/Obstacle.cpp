#include "Obstacle.h"
#include <include\math.h>

Obstacle::Obstacle()
{
}


Obstacle::~Obstacle()
{
}

Obstacle::Obstacle(float aangle, float heightO)
{
	count = 0;
	angle = aangle;
	moveAngle = 0.0f;
	height = heightO;
}


