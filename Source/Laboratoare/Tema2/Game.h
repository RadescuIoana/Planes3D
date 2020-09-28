#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include <Laboratoare\Tema2\Plane\Plane.h>
#include <Laboratoare\Tema2\Cloud\Cloud.h>
#include <Laboratoare\Tema2\Fuel\Fuel.h>
#include <Laboratoare\Tema2\Obstacle\Obstacle.h>

class Game : public SimpleScene
{
public:
	Game();
	~Game();

	Plane plane;

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));
	bool TestCollision(float x, float y, float px, float py, float len, float h);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	bool straight;
	glm::vec3 lightPosition;
	unsigned int materialShininess;
	float materialKd;
	float materialKs;
	float speed;
	float rotSeaAngle;
	float rotFuelAngle;
	float rotObsAngle;
	float rotCldAngle;
	float rotPropAngle;
	float sensivityOX;
	float sensivityOY;
	float planeMove;
	float angle;
	int random;
	int nLives;
	float maxFuel;
	bool gameOver;
	int orientation;
	float height;
	float heightO;
	float scaleFact;
	float px, py, fLen, fH, oLen, oH;
	float zSea;
	float xHeart, yHeart, zHeart;
	float xComb1, yComb1, zComb1;
	float xComb2, yComb2, zComb2;
	float rotateH, rotateC;
	int count;
	int countO;
	bool third_person;
	float falling;
	glm::mat4 propellerTranslateMatrix;
	std::vector<std::vector<Cloud>> clouds;
	std::vector<Fuel> fuel;
	std::vector<Obstacle> obstacles;
};
