#include "PhongMaterialWithTexture.h"

PhongMaterialWithTexture::PhongMaterialWithTexture():Material() {};
PhongMaterialWithTexture::PhongMaterialWithTexture(std::string sourcePath) :Material(sourcePath) {}
PhongMaterialWithTexture::PhongMaterialWithTexture(std::string materialSourcePath, std::shared_ptr<Texture> sharedTex) :Material(),texture(sharedTex){};
PhongMaterialWithTexture::PhongMaterialWithTexture(std::string textureSourcePath, int) :Material() 
{
	this->texture = std::make_unique<Texture>();
	this->texture->LoadFromFile(textureSourcePath);
};
PhongMaterialWithTexture::PhongMaterialWithTexture(std::string materialSourcePath,std::string textureSourcePath) :Material(materialSourcePath)
{
	this->texture = std::make_unique<Texture>();
	this->texture->LoadFromFile(textureSourcePath);
}

void PhongMaterialWithTexture::SetTexture(std::shared_ptr<Texture> tex)
{
	this->texture = tex;
}
void PhongMaterialWithTexture::Apply()
{
	if (this->texture != nullptr) 
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		this->texture->Apply();
	}
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(this->material[0]));
	glMaterialfv(GL_FRONT, GL_AMBIENT, glm::value_ptr(this->material[1]));
	glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(this->material[2]));
	glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(this->material[3]));
	glMaterialf(GL_FRONT, GL_SHININESS, this->shininess);
}