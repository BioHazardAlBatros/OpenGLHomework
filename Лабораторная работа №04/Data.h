#pragma once
#include <windows.h>
#include <vector>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "GraphicObject.h"

extern std::vector<glm::vec3> teapotColors;
extern std::vector<const char*> colorsName;
extern int colorsAmount;
extern int colorsIndex;

extern std::vector<GraphicObject> DrawQueue;

extern Camera MainCamera;//(10, 15, 17.5);

extern LARGE_INTEGER StartCounter, Frequency;

void initData();