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


class Mesh
{
private:
	struct Vertex
	{
		//glm::vec3 pos;
		//glm::vec3 normal;
		//glm::vec2 texPos;
		GLfloat pos[3];
		GLfloat normal[3];
		GLfloat texPos[2];
	};
	std::vector<Vertex> vertices;
public:
	void LoadFromFile(std::string sourcePath);
	void Draw();

};