#include "Light.h"

Light::Light()
{
	this->SetPosition({ 20.0,20.0,15.0 });
	this->SetAmbient({ 0,0,0,1 });
	this->SetDiffuse({ 1,1,1,1 });
	this->SetSpecular({ 1,1,1,1 });
}
Light::Light(glm::vec3 pos)
{
	this->SetPosition({ pos });
	this->SetAmbient({ 0.1,0.1,0.1,1 });
	this->SetDiffuse(glm::vec4(0));
	this->SetSpecular(glm::vec4(0));
}
Light::Light(float x, float y, float z)
{
	this->SetPosition({ x,y,z });
	this->SetAmbient({ 0.1,0.1,0.1,1 });
	this->SetDiffuse(glm::vec4(0));
	this->SetSpecular(glm::vec4(0));
}
void Light::SetPosition(glm::vec3 pos)
{
	this->position = { pos,1.0 };
}
void Light::SetAmbient(glm::vec4 color)
{
	this->ambient = color;
}
void Light::SetDiffuse(glm::vec4 color)
{
	this->diffuse = color;
}
void Light::SetSpecular(glm::vec4 color)
{
	this->specular = color;
}
void Light::Apply(GLenum LightNumber) 
{
	glLightfv(LightNumber, GL_POSITION, glm::value_ptr(this->position));
	glLightfv(LightNumber, GL_DIFFUSE, glm::value_ptr(this->diffuse));
	glLightfv(LightNumber, GL_AMBIENT, glm::value_ptr(this->ambient));
	glLightfv(LightNumber, GL_SPECULAR, glm::value_ptr(this->specular));
	glEnable(LightNumber);
};