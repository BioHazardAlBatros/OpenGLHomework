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

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include "Mesh.h"
#include "GraphicObject.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Texture.h"
#include "PhongMaterial.h"
#include "PhongMaterialWithTexture.h"
#include "GameObjectFactory.h"

extern GameObjectFactory gameObjFactory;

extern Camera MainCamera;//(10, 15, 17.5);
extern Light MainLight;
extern Light EnemyLight[3];

extern int pathMap[21][21];
// список игровых объектов расположенных на карте
extern std::shared_ptr<GameObject> mapObjects[21][21];
extern std::shared_ptr<GameObject> Player;
extern std::shared_ptr<GameObject> Enemy[3];
// графический объект для плоскости (частный случай)
extern std::shared_ptr<Texture> planeTexture;
extern GraphicObject planeGraphicObject;

extern LARGE_INTEGER StartCounter,Frequency;
void initData();
