#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
class Plane
{
	
public:
	Plane();
	~Plane();
	glm::mat4 translateMatrix;
	glm::mat4 rotateMatrix;
	void Plane::Move(float planeMove);
	void Rise();
	void Fall();
	float rotAngle;
	int rotations;
	int propSpeed;
	bool fall;

private:
	

};
