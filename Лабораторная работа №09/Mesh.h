#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>


#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/hash.hpp>

//bool glm::ivec3::operator==(const glm::ivec3& a, const glm::ivec3& b);
class Mesh
{
private:
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texPos;
	};
	//std::vector<Vertex> vertices;
	//std::vector<GLuint> indices;
	int indexCount;
	GLuint bufferIds[2];
public:
	Mesh();
	Mesh(std::string sourcePath);
	void LoadFromFile(std::string sourcePath);
	void Draw();
};