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

#include "GraphicObject.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

extern std::vector<glm::vec3> teapotColors;
//Количество доступных цветов
extern int colorsAmount;
//Текущий индекс в векторе цветов
extern int colorsIndex;
extern std::vector<GraphicObject> DrawQueue;
extern std::vector<std::shared_ptr<Material>> Materials;
extern Camera MainCamera;//(10, 15, 17.5);
extern Light MainLight;
extern GLfloat globalAmbientColor[4];

extern LARGE_INTEGER StartCounter,Frequency;
void initData();
