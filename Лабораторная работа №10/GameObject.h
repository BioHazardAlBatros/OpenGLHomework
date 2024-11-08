#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GraphicObject.h"

enum class MoveDirection
{
	STOP, LEFT, RIGHT, UP, DOWN
};

class GameObject
{
private:
	glm::ivec2 position;
	GraphicObject graphicObject;
	MoveDirection dir,lastdir;
	float speed, progress;
public:
	GameObject();
	void SetGraphicObject(const GraphicObject& object);
	void SetPosition(int x, int y);
	void SetPosition(glm::ivec2 pos);
	glm::ivec2 GetPosition();
	int GetLastDir();
	bool isMoving();
	void Draw();
	void Move(MoveDirection direction, float speed = 5.0f);
	void Simulate(float deltaTime);
};