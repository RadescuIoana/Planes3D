#include "Objects3D.h"

#include <Core/Engine.h>
using namespace std;

Mesh* Objects3D::CreateCilinder(const char* name, float length, glm::vec3 color)
{
	vector<VertexFormat>vertices;
	vector<unsigned short>indices;
	vector<glm::vec2> text_coords;
	glm::vec3 center = glm::vec3(0, 0, 0);


		
		for (int j = 0; j < 25; j++) {
			vertices.push_back(VertexFormat(center + glm::vec3(0, 0, j * length / 25), color));
			for (float i = 0; i < 150; i++) {
				float angle = i / 150.0 * 2 * 3.14;
				float random = (float) (rand() % 1000) / 1000;
				glm::vec2 tmp;
				tmp[0] = angle;
				tmp[1] = random;
				vertices.push_back(VertexFormat(center  + glm::vec3(0, 0, j * length / 25) + glm::vec3(cos(i / 150.0 * 2 * 3.14) * 1.5f, sin(i / 150.0 * 2 * 3.14) * 1.5f, 0), color, glm::vec3(0, 1, 0), tmp));
			}
		}

		
		for (int j = 0; j < 24; j++) {
			for (int i = 0; i < 150; i++) {
				indices.push_back(i + 1 + j * 150);
				indices.push_back(i + j * 150);
				indices.push_back(i + 150 + j * 150);

				indices.push_back(i + 1 + j * 150);
				indices.push_back(i + 150 + j * 150);
				indices.push_back(i + 151 + j * 150);
			}
		}
		

	Mesh* cilinder = new Mesh(name);

	cilinder->SetDrawMode(GL_TRIANGLE_STRIP);
	cilinder->InitFromData(vertices, indices);

	return cilinder;
}

