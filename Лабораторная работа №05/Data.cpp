#include "Data.h"

std::vector<glm::vec3> teapotColors;
int colorsAmount;
int colorsIndex;

std::vector<GraphicObject> DrawQueue;
Camera MainCamera;
Light MainLight;
GLfloat globalAmbientColor[4]= { 0.1, 0.1, 0.1, 1.0 };
std::vector<std::shared_ptr<Material>> Materials;
LARGE_INTEGER StartCounter,Frequency;

void initData()
{ 
	QueryPerformanceCounter(&StartCounter);
	QueryPerformanceFrequency(&Frequency);

	teapotColors = { {1.0,1.0,1.0},{0.0,0.0,1.0},{1.0,0.0,0.0},{1.0,1.0,0.0}, {1.0,0.0,1.0} };
	colorsAmount = teapotColors.size();
	MainCamera.SetPosition({ 10, 15, 17.5 });
	DrawQueue.push_back(GraphicObject({ -4.0,0.0,0.0 }, teapotColors[0], 0.0));
	
	DrawQueue.push_back(GraphicObject({ 0.0,0.0,4.0 }, teapotColors[1], 90.0));
	DrawQueue.push_back(GraphicObject({ 4.0,0.0,0.0 }, teapotColors[2], 180.0));
	DrawQueue.push_back(GraphicObject({ 0.0,0.0,-4.0 }, teapotColors[3], 270.0));
	
	for (int i = 0; i < 4; i++)
	{
		Materials.emplace_back(std::make_shared<Material>());
		DrawQueue[i].SetMaterial(Materials[i]);
	}
	Materials[0]->LoadFromFile(R"(assets/materials/mat1.txt)");
	Materials[1]->LoadFromFile(R"(assets/materials/mat2.txt)");
	Materials[2]->LoadFromFile(R"(assets/materials/mat3.txt)");
	Materials[3]->LoadFromFile(R"(assets/materials/mat4.txt)");
	//DrawQueue[0].SetMaterial(std::make_shared<Material>(glm::vec4{ 1,1,1,1 }, //Diffuse 
	//													glm::vec4{ 0,0,0,1 }, //Ambient
	//													glm::vec4{ 0,0,0,1 }, //Specular
	//													glm::vec4{ 0,0,0,1 }, 0.0));
	//
	//DrawQueue[1].SetMaterial(std::make_shared<Material>(glm::vec4{0,0,1,1}, //Diffuse 
	//													glm::vec4{0,0,0,1}, //Ambient
	//													glm::vec4{0,1,1,1}, //Specular
	//													glm::vec4{0,0,0,1},128.0));
	//
	//DrawQueue[2].SetMaterial(std::make_shared<Material>(glm::vec4{ 1,0,0,1 }, //Diffuse 
	//													glm::vec4{ 0,0,0,1 }, //Ambient
	//													glm::vec4{ 1,1,0,1 }, //Specular
	//													glm::vec4{ 0,0,0,1 }, 5.0));
	//
	//DrawQueue[3].SetMaterial(std::make_shared<Material>(glm::vec4{ 0,1,0,1 }, //Diffuse 
	//													glm::vec4{ 0,1,0,1 }, //Ambient
	//													glm::vec4{ 0,1,1,1 }, //Specular
	//													glm::vec4{ 0,0,0,1 }, 64.0));
}
