#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Objects3D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateCilinder(const char* name, float length, glm::vec3 color);

}

