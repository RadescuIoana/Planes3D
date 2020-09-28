#include "Plane.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Plane::Plane()
{
	translateMatrix = glm::mat4(1);
	translateMatrix= glm::translate(translateMatrix, glm::vec3(-1, 1, -0.7f));
	rotateMatrix = glm::mat4(1);
	rotAngle = 0.03f;
	propSpeed = 55;
	rotations = 0;
	fall = false;
}

Plane::~Plane()
{
}

void Plane::Move(float planeMove)
{
	if (planeMove >  0) {
		this->Fall();
		if (rotations > -15) {
			rotateMatrix = glm::rotate(rotateMatrix, rotAngle, glm::vec3(0.0f, 0.0f, 1.0f));
			rotations--;
		}
		
	} else if(planeMove < 0){
		this->Rise();
		if (rotations < 15) {
			rotateMatrix = glm::rotate(rotateMatrix, rotAngle, glm::vec3(0.0f, 0.0f, 1.0f));
			rotations++;
		}
	}else {
		if(rotations > 0){
			rotAngle = -abs(rotAngle);
			rotateMatrix = glm::rotate(rotateMatrix, rotAngle, glm::vec3(0.0f, 0.0f, 1.0f));
			rotations--;
		}
		else if (rotations < 0) {
			rotAngle = abs(rotAngle);
			rotateMatrix = glm::rotate(rotateMatrix, rotAngle, glm::vec3(0.0f, 0.0f, 1.0f));
			rotations++;
		}
	}

	translateMatrix = glm::translate(translateMatrix, glm::vec3(0.0f, -planeMove, 0.0f));
}

void Plane::Rise()
{
	fall = false;
	propSpeed = 100;
	rotAngle = abs(rotAngle);
}

void Plane::Fall()
{
	fall = true;
	propSpeed = 30;
	rotAngle = -abs(rotAngle);
}

