#pragma once
#include <include/glm.h>
#include <vector>

class Fuel
{
public:
	int count;
	int nEl;
	float height;
	float angle;
	std::vector<float> moveAngle;


	Fuel();
	Fuel(float aangle);
	~Fuel();
	
private:

};