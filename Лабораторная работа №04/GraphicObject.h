#pragma once
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class GraphicObject
{
private:
	glm::vec3 position;
	glm::vec3 color;
	float angle;
	GLfloat modelMatrix[16];
	void recalculateMatrix();
public:
	GraphicObject();
	GraphicObject(glm::vec3 pos,glm::vec3 color,float angle);
	void SetPosition(glm::vec3 newPosition);
	glm::vec3 GetPosition();

	void SetAngle(float newAngle);
	float GetAngle();

	void SetColor(glm::vec3 newColor);
	glm::vec3 GetColor();

	void draw();
};