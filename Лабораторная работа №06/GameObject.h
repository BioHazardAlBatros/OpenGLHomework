#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GraphicObject.h"

class GameObject
{
private:
	glm::ivec2 position;
	GraphicObject graphicObject;
public:
	GameObject();
	void SetGraphicObject(const GraphicObject& object);
	void SetPosition(int x, int y);
	void SetPosition(glm::ivec2 pos);
	glm::ivec2 GetPosition();
	void Draw();
};