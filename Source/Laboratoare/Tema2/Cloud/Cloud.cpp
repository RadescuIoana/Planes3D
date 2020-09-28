#include "Cloud.h"
#include <include\math.h>

Cloud::Cloud()
{
}


Cloud::~Cloud()
{
}

Cloud::Cloud(float ascaleFact, float az, float aangle)
{
	scaleFact = ascaleFact;
	rotate = RADIANS(rand() % 70 + 5);
	z = az;
	angle = aangle;
}



