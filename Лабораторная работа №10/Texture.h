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

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

enum class TextureFilter
{POINT,BILINEAR,TRILINEAR,ANISOTROPIC};
class Texture
{
	private:
		GLuint tIndex;
	public:
		static void DisableAll();
		void LoadFromFile(std::string sourcePath);
		void Apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);
};