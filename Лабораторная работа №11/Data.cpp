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
std::shared_ptr<GameObject> Enemy[3];
std::vector<Decal> Decals;
int MaxDecals;
GraphicObject planeGraphicObject;

void initData()
{
	std::srand(time(nullptr));
	QueryPerformanceCounter(&StartCounter);
	QueryPerformanceFrequency(&Frequency);

	MainCamera.SetPosition({ 0, 15, 17.5 });

	gameObjFactory.Init(R"(assets/GameObjectData.json)");
	Decal::Init();
	MaxDecals = 10;
	planeGraphicObject.SetMesh(std::make_unique<Mesh>(R"(assets\models\SimplePlane.obj)"));

	planeGraphicObject.SetMaterial(std::make_shared<PhongMaterialWithTexture>(R"(assets\materials\mat1.txt)", R"(assets\textures\fedya.jpg)"));
	//	planeGraphicObject.SetMaterial(std::make_shared<PhongMaterial>(R"(assets\materials\mat1.txt)"));

	planeGraphicObject.SetPosition({ 0,-0.501,0 });
	Player = gameObjFactory.Create(GameObjectFactory::GameObjectType::PLAYER, 9, -9);

	for (int i = 0; i < 3; i++)
	{
		int xPos = rand() % 21, yPos = rand() % 21;
		while (pathMap[xPos][yPos] != 0)
			xPos = rand() % 21, yPos = rand() % 21;

		Enemy[i] = gameObjFactory.Create(GameObjectFactory::ENEMY, xPos - 10, yPos - 10);
		pathMap[xPos][yPos] = 4;
		mapObjects[xPos][yPos] = Enemy[i];
	}

	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++) {
			switch (pathMap[i][j])
			{
			default: break;
			case 1:
				mapObjects[i][j] = gameObjFactory.Create(GameObjectFactory::GameObjectType::LIGHT_OBJECT, i - 10, j - 10);
				break;
			case 2:
				mapObjects[i][j] = gameObjFactory.Create(GameObjectFactory::GameObjectType::HEAVY_OBJECT, i - 10, j - 10);
				break;
			case 3:
				mapObjects[i][j] = gameObjFactory.Create(GameObjectFactory::GameObjectType::BORDER, i - 10, j - 10);
				break;
			}

		}
}

	printf("Data initialization complete.\n"); 
}