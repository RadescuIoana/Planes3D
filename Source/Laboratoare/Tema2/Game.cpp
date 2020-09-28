#include "Game.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include <Laboratoare\Tema2\Plane\Plane.h>
#include <Laboratoare\Tema2\Objects\Objects3D.h>
#include <Laboratoare\Tema2\Cloud\Cloud.h>

using namespace std;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	{
		Mesh* mesh = new Mesh("plane");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "plane.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("propeller");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "prop.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("heart");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "Heart.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("comb");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "quad.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("fuel");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "fuel.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}


	{
		Mesh* mesh = new Mesh("obstacle");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("cld");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = Objects3D::CreateCilinder("sea", 5, glm::vec3(0, 0, 1));
		meshes[mesh->GetMeshID()] = mesh;
	}
	
	{
		Shader* shader = new Shader("Game");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("SeaShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/SeaVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/SeaFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("Plane");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/PlaneVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/PlaneFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	srand(NULL);
	for(int j = 0; j < 8; j++) {
		std::vector<Cloud> cloud;
		float z = (float)((rand() % 200 + 150) * 0.01f);
		z *= (-1);
		float angle = (float)((rand()% 628) * 0.01f);
		for (int i = 0; i < 4; i++) {
			scaleFact = (float)((rand() % 35 + 25) * 0.01f);
			Cloud c = Cloud(scaleFact, z, angle);
			cloud.push_back(c);
		}
		clouds.push_back(cloud);
	}

	for (int j = 0; j < 8; j++) {
		float angle = (float)((rand() % 628) * 0.01f);
		Fuel f = Fuel(angle);
		fuel.push_back(f);
	}


	for (int j = 0; j < 8; j++) {
		float angle = (float)((rand() % 628) * 0.01f);
		if (fuel[j].height >= 1.5f) {
			heightO = fuel[j].height - 0.5f;
		}
		else {
			heightO = fuel[j].height + 0.5f;
		}
		Obstacle o = Obstacle(angle, heightO);
		obstacles.push_back(o);
	}
	
	third_person = true;
	lightPosition = glm::vec3(0, 2, -1);
	materialShininess = 30;
	materialKd = 0.5;
	materialKs = 0.5;
	speed = 0.5f;
	sensivityOX = 0.003f;
	sensivityOY = 0.003f;
	rotSeaAngle = 0;
	rotCldAngle = 0;
	rotFuelAngle = 0;
	rotPropAngle = 0.01f;
	angle = RADIANS(45.0f);
	random = rand() % 125;
	plane = Plane();
	straight = true;
	maxFuel = 0.7f;
	nLives = 3;
	gameOver = false;
	height = (float)((rand() % 200 + 100) / 100);
	count = 0;
	countO = 0;
	zSea = -2.5f;
	xHeart = 4.8f;
	yHeart = 2.3f;
	zHeart = -2.5f;
	xComb1 = 2.90f;
	xComb2 = 2.90f;
	yComb1 = 2.4f;
	yComb2 = 2.4f;
	zComb1 = -1.49f;
	zComb2 = -1.5f;
	falling = 0;
}

void Game::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(1.0f, 0.9f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Game::Update(float deltaTimeSeconds)
{
	if (gameOver == false) {
		rotSeaAngle += speed * deltaTimeSeconds;
		rotFuelAngle += deltaTimeSeconds * speed;
		rotCldAngle += deltaTimeSeconds * speed;
		rotObsAngle += deltaTimeSeconds * speed;
	}
	else {
		falling += speed * deltaTimeSeconds;
		if (falling > 1) {
			Game::Init();
		}
	}

	if (third_person) {
		xHeart = 4.8f;
		yHeart = 2.3f;
		zHeart = -2.5f;
		xComb1 = 2.90f;
		xComb2 = 2.90f;
		yComb1 = 2.4f;
		yComb2 = 2.4f;
		zComb1 = -1.49f;
		zComb2 = -1.5f;
	}
	else {
		xHeart = -1.5f;
		yHeart = 2.5f;
		zHeart = -3.8f;
		xComb1 = 0.09f;
		xComb2 = 0.10f;
		yComb1 = 3.4f;
		yComb2 = 3.4f;
		zComb1 = 1.64f;
		zComb2 = 1.64f;
	}
	if (nLives == 0) {
		gameOver = true;
	}
	if (straight) {
		plane.Move(0);
	}
	straight = true;
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(xComb1, yComb1, zComb1));
		if (third_person == false) {
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		modelMatrix = glm::scale(modelMatrix, glm::vec3(maxFuel, 0.1f, 0));
		if (gameOver == false) {
			RenderSimpleMesh(meshes["comb"], shaders["Game"], modelMatrix, glm::vec3(0.16f, 0.58f, 0.00f));
		}
		if (maxFuel <= 0) {
			maxFuel = 0.7f;
			nLives -= 1;
		} else {
			float angle = deltaTimeSeconds * speed;
			angle /= 7.28f;
			maxFuel -= angle;
		}
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(xComb2, yComb2, zComb2));
		if (third_person == false) {
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f, 0.15f, 0));
		if (gameOver == false) {
			RenderSimpleMesh(meshes["comb"], shaders["Game"], modelMatrix, glm::vec3(0.00f, 0.00f, 0.00f));
		}
	}

	for (int i = 0; i < nLives; i++) {

		glm::mat4 modelMatrix = glm::mat4(1);
		if (third_person == true) {
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-(xHeart - 0.6f * i), yHeart, zHeart));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else {
			modelMatrix = glm::translate(modelMatrix, glm::vec3(xHeart, yHeart, zHeart + 0.5f*i));
		}
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderSimpleMesh(meshes["heart"], shaders["Game"], modelMatrix, glm::vec3(1.00f, 0.40f, 0.60f));

	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -4.5f, zSea));
		modelMatrix = glm::rotate(modelMatrix, rotSeaAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(3));
		RenderSimpleMesh(meshes["sea"], shaders["SeaShader"], modelMatrix, glm::vec3(0.00f, 0.58f, 0.60f));
	}

	for(int j = 0; j < 8; j++) {
		for (int i = 0; i < 4; i++) {
			float aux = i * 0.05f + j;
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -4.5f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, rotCldAngle * 0.5f + clouds[j][i].angle + aux, glm::vec3(0.0f, 0.0f, 1.0f));
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 4.5f + height, clouds[j][i].z));
			modelMatrix = glm::rotate(modelMatrix, clouds[j][i].rotate, glm::vec3(0.0f, 0.0f, 1.0f));
			if (i % 2 == 0) {
				modelMatrix = glm::rotate(modelMatrix, rotSeaAngle, glm::vec3(0.0f, 1.0f, 0.0f));
			}
			modelMatrix = glm::scale(modelMatrix, glm::vec3(clouds[j][i].scaleFact));
			
			RenderSimpleMesh(meshes["cld"], shaders["Plane"], modelMatrix, glm::vec3(1.00f, 0.67f, 0.50f));
		}
	}
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		if (gameOver == false) {
			modelMatrix *= plane.translateMatrix;
			modelMatrix *= plane.rotateMatrix;
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
			px = modelMatrix[3][0];
			py = modelMatrix[3][1];
			RenderSimpleMesh(meshes["plane"], shaders["Plane"], modelMatrix, glm::vec3(1.00f, 0.00f, 0.17f));
		} else {
			modelMatrix *= plane.translateMatrix;
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -falling*4, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, -falling*4, glm::vec3(0.0f, 0.0f, 1.0f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
			RenderSimpleMesh(meshes["plane"], shaders["Plane"], modelMatrix, glm::vec3(1.00f, 0.00f, 0.17f));
			
		}	
	}

	if (gameOver == false) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= plane.translateMatrix;
		modelMatrix *= plane.rotateMatrix;
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		modelMatrix = glm::rotate(modelMatrix, rotSeaAngle * plane.propSpeed, glm::vec3(1.0f, 0.0f, 0.0f));
		RenderSimpleMesh(meshes["propeller"], shaders["Plane"], modelMatrix, glm::vec3(1.00f, 1.00f, 1.00f));
	}
	else {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= plane.translateMatrix;
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -falling * 4, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, -falling * 4, glm::vec3(0.0f, 0.0f, 1.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
		RenderSimpleMesh(meshes["propeller"], shaders["Plane"], modelMatrix, glm::vec3(1.00f, 1.00f, 1.00f));

	}

	for (int i = 0; i < 8; i++) {
		glm::mat4 modelMatrix = glm::mat4(1);
		float aux = rotObsAngle * 0.7f + obstacles[i].angle + i;
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -4.5f, -0.67f));
		modelMatrix = glm::rotate(modelMatrix, aux, glm::vec3(0.0f, 0.0f, 1.0f));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, (4.5f + obstacles[i].height), 0));
		modelMatrix = glm::rotate(modelMatrix, rotObsAngle * 8, glm::vec3(0.00f, 0.00f, 1.00f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4f));
		float x = modelMatrix[3][0];
		float y = modelMatrix[3][1];
		oLen = 0.2f;
		oH = 0.2f;
		if (obstacles[i].moveAngle + 3 < aux || obstacles[i].moveAngle == 0) {
			RenderSimpleMesh(meshes["obstacle"], shaders["Game"], modelMatrix, glm::vec3(1.00f, 0.55f, 0.75f));
			obstacles[i].moveAngle = 0;
			if (TestCollision(x, y, px, py, oLen, oH) == true) {
				nLives--;
				obstacles[i].moveAngle = aux;
			}
		}
		
		if ((aux / 7.2f) >= obstacles[i].count) {
			obstacles[i].count++;
			if (fuel[i].height >= 1.5f) {
				obstacles[i].height = fuel[i].height - 0.5f;
			}
			else {
				obstacles[i].height = fuel[i].height + 0.5f;
			}
		}
	}

	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < fuel[j].nEl; i++) {
			glm::mat4 modelMatrix = glm::mat4(1);
			float aux = rotFuelAngle + fuel[j].angle + i * 0.03f + j;
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -4.5f, -0.67f));
			modelMatrix = glm::rotate(modelMatrix, aux, glm::vec3(0.0f, 0.0f, 1.0f));
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 4.5f + fuel[j].height, 0));
			modelMatrix = glm::rotate(modelMatrix, rotFuelAngle * 4, glm::vec3(0.00f, 0.00f, 1.00f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.0008f));
			float x = modelMatrix[3][0];
			float y = modelMatrix[3][1];
			fLen = 0.12f;
			fH = 0.12f;
			if (fuel[j].moveAngle[i] + 3 <= aux || fuel[j].moveAngle[i] == 0) {
				fuel[j].moveAngle[i] = 0;
				if (TestCollision(x, y, px, py, fLen, fH) == true) {

					fuel[j].moveAngle[i] = aux;
					if (maxFuel <= 0.7f) {
						maxFuel += 0.05f;
					}
				}
				else {
					RenderSimpleMesh(meshes["fuel"], shaders["Game"], modelMatrix, glm::vec3(0.00f, 0.45f, 0.35f));

				}
			}
			if ((aux / 7.2f) >= fuel[j].count) {
				fuel[j].count++;
				fuel[j].height = (float)((rand() % 200 + 100) / 100);
			}
		}
	}
		
}

void Game::FrameEnd()
{
}

void Game::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Set shader uniforms for light & material properties
	// TODO: Set light position uniform
	int location = glGetUniformLocation(shader->GetProgramID(), "light_position");
	glUniform3fv(location, 1, glm::value_ptr(lightPosition));

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
	location = glGetUniformLocation(shader->GetProgramID(), "eye_position");
	glUniform3fv(location, 1, glm::value_ptr(eyePosition));

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	location = glGetUniformLocation(shader->GetProgramID(), "material_shininess");
	glUniform1i(location, materialShininess);
	location = glGetUniformLocation(shader->GetProgramID(), "material_kd");
	glUniform1f(location, materialKd);
	location = glGetUniformLocation(shader->GetProgramID(), "material_ks");
	glUniform1f(location, materialKs);
	location = glGetUniformLocation(shader->GetProgramID(), "object_color");
	glUniform3fv(location, 1, glm::value_ptr(color));

	location = glGetUniformLocation(shader->GetProgramID(), "Time");
	glUniform1f(location, Engine::GetElapsedTime());

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

bool Game::TestCollision(float x, float y, float px, float py, float len, float h)
{
	float planeLen1 = 0.42f;
	float planeLen2 = 0.3f;
	float planeH1 = 0.19f;
	float planeH2 = 0.13f;
	if (px - planeLen1 >= x - len && px - planeLen1 <= x + len) {
		if (py + planeH2 >= y - h && py + planeH2 <= y + h) {
			return true;
		} 
		if (py - planeH1 >= y - h && py - planeH1 <= y + h) {
			return true;
		}
	} 
	if (px + planeLen2 > x - len && px + planeLen2 <= x + len) {
		if (py + planeH2 >= y - h && py + planeH2 <= y + h) {
			return true;
		}
		if (py - planeH1 >= y - h && py - planeH1 <= y + h) {
			return true;
		}
	}
	return false;
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Game::OnInputUpdate(float deltaTime, int mods)
{
}
void Game::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_C) {
		if (third_person) {
			third_person = false;
			GetSceneCamera()->SetPerspective(60, window->props.aspectRatio, 0.01f, 200);
			GetSceneCamera()->transform->SetMoveSpeed(2);
			GetSceneCamera()->transform->SetWorldPosition(glm::vec3(-4, 1.5, -0.7f));
			GetSceneCamera()->transform->RotateLocalOY(-1.7);
			GetSceneCamera()->transform->RotateLocalOZ(-0.3);
			GetSceneCamera()->Update();
		}
		else {
			third_person = true;
			GetSceneCamera()->SetPerspective(60, window->props.aspectRatio, 0.01f, 200);
			GetSceneCamera()->transform->SetWorldPosition(glm::vec3(0, 1.6f, 2.5));
			GetSceneCamera()->transform->SetWorldRotation(glm::vec3(-15, 0, 0));
			GetSceneCamera()->Update();
		}
	}
}

void Game::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Game::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (gameOver == false) {
		// add mouse move event
		planeMove = deltaY * sensivityOY;
		//movePlane
		straight = false;
		plane.Move(planeMove);
		propellerTranslateMatrix = glm::translate(plane.translateMatrix, glm::vec3(0.0f, -planeMove, 0.0f));
		if (!third_person) {
			GetSceneCamera()->transform->SetWorldPosition(glm::vec3(-4, 1.5 + -planeMove / 10, -0.7));
			zSea = -5.0f;
			GetSceneCamera()->Update();
		}
	}
}

void Game::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Game::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Game::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Game::OnWindowResize(int width, int height)
{
}