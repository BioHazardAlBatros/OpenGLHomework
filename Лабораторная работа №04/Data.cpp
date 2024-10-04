#include "Data.h"

std::vector<glm::vec3> teapotColors;
std::vector<const char*> colorsName;
int colorsAmount;
int colorsIndex;
std::vector<GraphicObject> DrawQueue;
Camera MainCamera;
LARGE_INTEGER StartCounter,Frequency;

void initData()
{
	QueryPerformanceCounter(&StartCounter);
	QueryPerformanceFrequency(&Frequency);
	teapotColors = { {1.0,1.0,1.0},{0.0,0.0,1.0},{1.0,0.0,0.0},{1.0,1.0,0.0}, {1.0,0.0,1.0} };
	colorsName = { "white", "blue", "red", "yellow", "purple" };
	colorsAmount = teapotColors.size();
	MainCamera.SetPosition({ 10, 15, 17.5 });
	DrawQueue.push_back(GraphicObject({ -4.0,0.0,0.0 }, teapotColors[0], 0.0));
	DrawQueue.push_back(GraphicObject({ 0.0,0.0,4.0 }, teapotColors[1], 90.0));
	DrawQueue.push_back(GraphicObject({ 4.0,0.0,0.0 }, teapotColors[2], 180.0));
	DrawQueue.push_back(GraphicObject({ 0.0,0.0,-4.0 }, teapotColors[3], 270.0));
}
