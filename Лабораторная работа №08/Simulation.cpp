#include "Simulation.h"

double getSimulationTime()
{
	LARGE_INTEGER temp;
	QueryPerformanceCounter(&temp);
	double tempd = temp.QuadPart;
	return (tempd - StartCounter.QuadPart) / Frequency.QuadPart;
}

int getFPS()
{
	static int frameCount = 0;
	static int FPS = 0;
	static double timeElapsed;
	++frameCount;
	timeElapsed = getSimulationTime();
	if (timeElapsed >= 1.0)
	{	
		QueryPerformanceCounter(&StartCounter);
		FPS = frameCount;
		frameCount = 0;
	}
	return FPS;
}
void MovePlayer()
{
	static struct { int key, x1, y1, x2, y2; MoveDirection dir; } 
	Moves[4]
	{
		{0x41,9,10,8,10,MoveDirection::LEFT},
		{0x44,11,10,12,10,MoveDirection::RIGHT},
		{0x57,10,9,10,8,MoveDirection::UP},
		{0x53,10,11,10,12,MoveDirection::DOWN}
	};
	glm::ivec2 playerPos = Player->GetPosition();
	for (auto move : Moves) 
	{
		if (static_cast<bool>(GetAsyncKeyState(move.key)) && !Player->isMoving() && pathMap[playerPos.x + move.x1][playerPos.y + move.y1] <= 1)
		if (pathMap[playerPos.x + move.x1][playerPos.y + move.y1] == 1 && pathMap[playerPos.x + move.x2][playerPos.y + move.y2] == 0)
		{
			mapObjects[playerPos.x + move.x1][playerPos.y + move.y1]->Move(move.dir);
			Player->Move(move.dir);
			std::swap(pathMap[playerPos.x + move.x1][playerPos.y + move.y1], pathMap[playerPos.x + move.x2][playerPos.y + move.y2]);
			std::swap(mapObjects[playerPos.x + move.x1][playerPos.y + move.y1], mapObjects[playerPos.x + move.x2][playerPos.y + move.y2]);
		}
		else if (pathMap[playerPos.x + move.x1][playerPos.y + move.y1] == 0)
			Player->Move(move.dir);
	}
}
void CameraSimulation(float deltaTime)
{
	static float rotateSpeed = 90.0;
	static float leanSpeed = 1.f;
	if (static_cast<bool>(GetAsyncKeyState(VK_LEFT)))  MainCamera.RotateLeftRight(rotateSpeed * deltaTime);
	if (static_cast<bool>(GetAsyncKeyState(VK_RIGHT))) MainCamera.RotateLeftRight(-rotateSpeed * deltaTime);
	if (static_cast<bool>(GetAsyncKeyState(VK_UP)))	 MainCamera.RotateUpDown(2 * rotateSpeed * deltaTime);
	if (static_cast<bool>(GetAsyncKeyState(VK_DOWN)))  MainCamera.RotateUpDown(-2 * rotateSpeed * deltaTime);
	if (static_cast<bool>(GetAsyncKeyState(VK_SUBTRACT))) MainCamera.ZoomOutin(40 * deltaTime);
	if (static_cast<bool>(GetAsyncKeyState(VK_ADD)))	  MainCamera.ZoomOutin(-40 * deltaTime);
	if (static_cast<bool>(GetAsyncKeyState(0x45)))		  MainCamera.LeanLeftRight(-leanSpeed * deltaTime);
	if (static_cast<bool>(GetAsyncKeyState(0x51)))	      MainCamera.LeanLeftRight(leanSpeed * deltaTime);
	return;
}
void GameObjectsSimulation(float deltaTime)
{
	Player->Simulate(deltaTime);
	for (auto& i : mapObjects)
		for (auto& j : i)
			if (j != nullptr)j->Simulate(deltaTime);

}
void simulation()
{
	static double PrevTime = StartCounter.QuadPart;
	LARGE_INTEGER CurrTime;
	QueryPerformanceCounter(&CurrTime);
	double deltaTime = (CurrTime.QuadPart - PrevTime)/Frequency.QuadPart;
	PrevTime = CurrTime.QuadPart;

	CameraSimulation(deltaTime);
	GameObjectsSimulation(deltaTime);
	
	MovePlayer();
	
	glutPostRedisplay();
}