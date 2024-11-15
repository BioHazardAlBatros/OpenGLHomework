#include "PhongMaterial.h"

PhongMaterial::PhongMaterial() :Material() {};
PhongMaterial::PhongMaterial(std::string sourcePath) :Material(sourcePath) {}


void PhongMaterial::Apply()
{
	Texture::DisableAll();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(this->material[0]));
	glMaterialfv(GL_FRONT, GL_AMBIENT, glm::value_ptr(this->material[1]));
	glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(this->material[2]));
	glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(this->material[3]));
	glMaterialf(GL_FRONT, GL_SHININESS, this->shininess);
}