#pragma once
#include <include/glm.h>

class Cloud
{
public:
	float scaleFact;
	float rotate;
	float dist;
	float height;
	float angle;
	float z;

	Cloud();
	Cloud(float ascaleFact, float z, float aangle);
	~Cloud();

private:

};