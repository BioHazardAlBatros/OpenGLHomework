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

#include "Mesh.h"
#include "GraphicObject.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

extern std::vector<glm::vec3> teapotColors;

extern std::vector<GraphicObject> DrawQueue;
extern std::vector<std::shared_ptr<Material>> Materials;
extern std::vector<std::shared_ptr<Mesh>> Meshes;

extern Camera MainCamera;//(10, 15, 17.5);
extern Light MainLight;

extern int pathMap[21][21];
// список игровых объектов расположенных на карте
extern std::shared_ptr<GameObject> mapObjects[21][21];
// графический объект для плоскости (частный случай)
extern GraphicObject planeGraphicObject;

extern LARGE_INTEGER StartCounter,Frequency;
void initData();
