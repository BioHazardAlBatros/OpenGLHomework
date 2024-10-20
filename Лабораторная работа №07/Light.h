#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
	private:
	glm::vec4 position,ambient, diffuse, specular;
	public:
	Light();
	Light(glm::vec3 pos);
	Light(float x, float y, float z);

	void SetPosition(glm::vec3 pos);
	void SetAmbient(glm::vec4 color);
	void SetDiffuse(glm::vec4 color);
	void SetSpecular(glm::vec4 color);

	void Apply(GLenum LightNumber = GL_LIGHT0);
};