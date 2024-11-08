#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Mesh
{
private:
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texPos;
		//GLfloat pos[3]; 12
		//GLfloat normal[3]; 12
		//GLfloat texPos[2]; 8
	};
	std::vector<Vertex> vertices;
public:
	Mesh();
	Mesh(std::string sourcePath);
	void LoadFromFile(std::string sourcePath);
	void Draw();
};