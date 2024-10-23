#include "Data.h"

GameObjectFactory gameObjFactory;

Camera MainCamera;
Light MainLight;

LARGE_INTEGER StartCounter,Frequency;

int pathMap[21][21]{
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};
std::shared_ptr<GameObject> mapObjects[21][21];
std::shared_ptr<GameObject> Player;

GraphicObject planeGraphicObject;

void initData()
{ 
	QueryPerformanceCounter(&StartCounter);
	QueryPerformanceFrequency(&Frequency);

	MainCamera.SetPosition({ 0, 15, 17.5 });

	gameObjFactory.Init(R"(assets/GameObjectData.json)");
	planeGraphicObject.SetMesh(std::make_unique<Mesh>(R"(assets\models\SimplePlane.obj)"));
	planeGraphicObject.SetMaterial(std::make_unique<Material>(R"(assets\materials\mat1.txt)"));
	planeGraphicObject.SetPosition({ 0,-0.501,0 });

	Player = gameObjFactory.Create(GameObjectFactory::GameObjectType::PLAYER, 9, -9);

	for(int i = 0 ;i<21;i++)
		for(int j=0;j<21;j++)
				switch (pathMap[i][j])
				{
				default: break;
				case 1:
					mapObjects[i][j] = gameObjFactory.Create(GameObjectFactory::GameObjectType::LIGHT_OBJECT, i-10, j-10);
					break;
				case 2:
					mapObjects[i][j] = gameObjFactory.Create(GameObjectFactory::GameObjectType::HEAVY_OBJECT, i - 10, j - 10);
					break;
				case 3:
					mapObjects[i][j] = gameObjFactory.Create(GameObjectFactory::GameObjectType::BORDER, i - 10, j - 10);
					break;
				}
}