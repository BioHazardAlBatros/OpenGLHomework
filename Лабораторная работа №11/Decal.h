#pragma once
#include "GraphicObject.h"

class Decal 
{
	glm::ivec2 position;
	GraphicObject graphicObject;
	static std::shared_ptr<PhongMaterialWithTexture> decalTexture;
	static std::shared_ptr<Mesh> decalMesh;
	public:
		Decal();
		Decal(glm::ivec2);
		static void Init();
		void Draw();
};