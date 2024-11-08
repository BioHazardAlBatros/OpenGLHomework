#pragma once
#include <windows.h> //Required for RapidJSON
#include <document.h> //RapidJSON Document.h
#include <istreamwrapper.h> //RapidJSON istreamwrapper.h
//#include <set>

#include "Mesh.h"
#include "Material.h"
#include "GraphicObject.h"
#include "GameObject.h"

class GameObjectFactory
{
private:
	std::vector<std::shared_ptr<Material>> Materials;
	std::vector<std::shared_ptr<Mesh>> Meshes;
public:
	enum GameObjectType
	{
		LIGHT_OBJECT, HEAVY_OBJECT, BORDER, PLAYER, ENEMY,BOMB
	};
	bool Init(std::string sourcePath);
	std::shared_ptr<GameObject> Create(GameObjectType type, glm::vec2 pos);
	std::shared_ptr<GameObject> Create(GameObjectType type, int x, int y);
};