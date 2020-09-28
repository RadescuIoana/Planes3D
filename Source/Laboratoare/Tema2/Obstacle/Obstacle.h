#pragma once
#include <include/glm.h>

class Obstacle
{
public:
	int count;
	float height;
	float angle;
	float moveAngle;

	Obstacle();
	Obstacle(float aangle, float heightO);
	~Obstacle();
	
private:

};