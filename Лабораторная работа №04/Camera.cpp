#include "Camera.h"

void Camera::RotateLeftRight(float degree)
{
	this->angle.x +=degree;
	this->RecalculatePosition();
	return;
}
void Camera::RotateUpDown(float degree)
{
	this->rotation.y = cos(glm::radians(this->angle.y + degree)) > 0 ? 1 : -1;
	this->angle.y = fmod(this->angle.y+degree, 360.0f);
	this->RecalculatePosition();
	return;
}
void Camera::LeanLeftRight(float degree)
{
	if (abs(this->rotation.x+degree) > 5.0f)return;
	this->rotation.x +=degree;
	return;
}
void Camera::ZoomOutin(float distance)
{
	if (this->radius + distance > 50 || this->radius + distance < 5) return;
	this->radius += distance;
	this->RecalculatePosition();
	return;
}
void Camera::RecalculatePosition()
{
	float radiusX    = this->radius * cos(glm::radians(this->angle.y));
	this->position.y = this->radius  * sin(glm::radians(this->angle.y));
	this->position.x = radiusX * cos(glm::radians(this->angle.x));
	this->position.z = radiusX * sin(glm::radians(this->angle.x));
	return;
}
Camera::Camera(glm::vec3 position)
{
	this->rotation.y = 1;
	this->SetPosition(position); return;
}
Camera::Camera(float x, float y, float z)
{
	this->rotation.y=1;
	this->SetPosition(glm::vec3(x, y, z)); return;
}
Camera::Camera()
{
	this->rotation.y=1;
	this->SetPosition(glm::vec3(1, 0, 0)); return;
}
void Camera::SetTarget(glm::vec3 target)
{
	this->target = target;
	return;
}
glm::vec3 Camera::GetTarget()
{
	return this->target;
}
glm::vec3 Camera::GetPosition()
{
	return this->position;
}
Camera::angleStruct Camera::GetAngle()
{
	return this->angle;
}
void Camera::SetPosition(glm::vec3 position)
{
	this->radius = glm::length(position);
	glm::vec3 temp = glm::vec3(position.x, 0.0, position.z);
	float cos_y = glm::dot(glm::normalize(position), glm::normalize(temp));
	float cos_x = glm::dot(glm::normalize(temp), glm::vec3(1.0, 0.0, 0.0));
	this->angle.y = glm::degrees(acos(cos_y));
	this->angle.x = glm::degrees(acos(cos_x));
	this->RecalculatePosition();
	return;
}
void Camera::Apply()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();																								//RotationVector
	gluLookAt(this->position.x, this->position.y, this->position.z, this->target.x, this->target.y, this->target.z, 
		this->rotation.x, this->rotation.y, this->rotation.z);
	return;
}