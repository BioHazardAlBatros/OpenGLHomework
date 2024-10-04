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


class Material
{
	private:
	std::vector<glm::vec4> material;
	float shininess;

	public:
	Material();
	Material(glm::vec4 diffuse, glm::vec4 ambient, glm::vec4 specular,glm::vec4 emission, float shininess);
	void LoadFromFile(std::string sourcePath);
	void SetDiffuse(glm::vec4 color);
	void SetAmbient(glm::vec4 color);
	void SetSpecular(glm::vec4 color);
	void SetEmission(glm::vec4 color);
	void SetShininess(float percent);
	void Apply();
};