#pragma once
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
	struct angleStruct { float x,y; } angle;
	float  radius;
	glm::vec3 position, target,rotation;
	void RecalculatePosition();
public:
	Camera();
	Camera(glm::vec3 position);
	Camera(float x, float y, float z);
	void SetPosition(glm::vec3);
	void SetTarget(glm::vec3);

	glm::vec3 GetPosition();
	glm::vec3 GetTarget();
	angleStruct GetAngle();
	void RotateLeftRight(float degree);
	void RotateUpDown(float degree);
	void LeanLeftRight(float degree);
	void ZoomOutin(float distance);
	void Apply();
};