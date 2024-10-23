#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>

#include <GL/glew.h>
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
#include "GameObjectFactory.h"

extern GameObjectFactory gameObjFactory;

extern Camera MainCamera;//(10, 15, 17.5);
extern Light MainLight;

extern int pathMap[21][21];
// список игровых объектов расположенных на карте
extern std::shared_ptr<GameObject> mapObjects[21][21];
extern std::shared_ptr<GameObject> Player;
// графический объект для плоскости (частный случай)
extern GraphicObject planeGraphicObject;

extern LARGE_INTEGER StartCounter,Frequency;
void initData();
