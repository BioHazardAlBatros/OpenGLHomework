#include "Data.h"
#include "Material.h"
Material::Material()
{
	this->material.push_back(glm::vec4(.8,.8,.8,1)); //diffuse
	this->material.push_back(glm::vec4(.2, .2, .2, 1)); //ambient
	this->material.push_back(glm::vec4(.0, .0, .0, 1)); //specular
	this->material.push_back(glm::vec4(.0, .0, .0, 1)); //emission
	this->shininess = .0;
}
Material::Material(glm::vec4 diffuse, glm::vec4 ambient, glm::vec4 specular,glm::vec4 emission, float shininess)
{
	this->material.push_back(diffuse);
	this->material.push_back(ambient);
	this->material.push_back(specular);
	this->material.push_back(emission);
	this->shininess = shininess;
}
void Material::SetDiffuse(glm::vec4 color) 
{
	this->material[0] = color;
};
void Material::SetAmbient(glm::vec4 color) 
{
	this->material[1] = color;
};
void Material::SetSpecular(glm::vec4 color) 
{
	this->material[2] = color;
};
void Material::SetEmission(glm::vec4 color) 
{
	this->material[3] = color;
};
void Material::SetShininess(float percent) 
{
	this->shininess = fmod(percent,128.0);
};
void Material::LoadFromFile(std::string sourcePath)
{
	std::ifstream File(sourcePath);
	if (!File)
	{
		std::cerr << "\nFailed to load from "<<sourcePath;
		return;
	}
	std::cout << "\nLoading material data from " << sourcePath<<'\n';
	std::string currentFieldName;
	for (int j = 0; j < 4; j++)
	{
		File >> currentFieldName;
		std::cout << currentFieldName<<' ';
		for (int i = 0; i < 4; i++)
		{
			File >> (this->material[j])[i];
			std::cout << (this->material[j])[i]<<' ';
		}
		std::cout << '\n';
	}
	File >> currentFieldName;
	File >> this->shininess;
	std::cout << currentFieldName << ' '<<this->shininess << std::endl;
}
void Material::Apply()
{
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(this->material[0]));
	glMaterialfv(GL_FRONT, GL_AMBIENT, glm::value_ptr(this->material[1]));
	glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(this->material[2]));
	glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(this->material[3]));
	glMaterialf(GL_FRONT, GL_SHININESS, this->shininess);
}