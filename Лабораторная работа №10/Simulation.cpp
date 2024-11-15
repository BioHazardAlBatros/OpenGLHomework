#include "Simulation.h"

double getSimulationTime()
{
	LARGE_INTEGER temp;
	QueryPerformanceCounter(&temp);
	return temp.QuadPart - StartCounter.QuadPart;
}

int getFPS()
{
	static int frameCount = 0;
	static int FPS = 0;
	++frameCount;
	if (getSimulationTime() >= Frequency.QuadPart)
	{	
		QueryPerformanceCounter(&StartCounter);
		FPS = frameCount;
		frameCount = 0;
	}
	return FPS;
}

void MoveEnemy(std::shared_ptr<GameObject>& entity)
{
	static struct { int key, x1, y1, x2, y2; MoveDirection dir; }
	Moves[4]
	{
		{0,9,10,8,10,MoveDirection::LEFT},
		{1,11,10,12,10,MoveDirection::RIGHT},
		{2,10,9,10,8,MoveDirection::UP},
		{3,10,11,10,12,MoveDirection::DOWN}
	};
	glm::ivec2 entityPos = entity->GetPosition();
	int PickMove = entity->GetLastDir();
//	int PickMove = rand() % 4;
	if (!entity->isMoving() && pathMap[entityPos.x + Moves[PickMove].x1][entityPos.y + Moves[PickMove].y1] == 0)
	{
			entity->Move(Moves[PickMove].dir,3);
			std::swap(pathMap[entityPos.x + Moves[PickMove].x1][entityPos.y + Moves[PickMove].y1], 
					  pathMap[entityPos.x + 10][entityPos.y + 10]);
	}

}

void MovePlayer()
{
//	MainLight.SetPosition({Player->GetPosition().x, 10, Player->GetPosition().y});
	static struct { int key, x1, y1, x2, y2; MoveDirection dir; } 
	Moves[4]
	{
		{0x41,9,10,8,10,MoveDirection::LEFT},
		{0x44,11,10,12,10,MoveDirection::RIGHT},
		{0x57,10,9,10,8,MoveDirection::UP},
		{0x53,10,11,10,12,MoveDirection::DOWN}
	};
	glm::ivec2 playerPos = Player->GetPosition();
	if (pathMap[playerPos.x + 10][playerPos.y + 10] == 4)
	{
		Player.reset();
		system("cls");
		printf_s("\tChange the world... My final message... Goodbye.");
		return;
	}
	for (auto move : Moves) 
	{
		if (static_cast<bool>(GetAsyncKeyState(move.key)) && !Player->isMoving() && pathMap[playerPos.x + move.x1][playerPos.y + move.y1] <= 1)
		if (pathMap[playerPos.x + move.x1][playerPos.y + move.y1] == 1 && pathMap[playerPos.x + move.x2][playerPos.y + move.y2] == 0)
		{
			mapObjects[playerPos.x + move.x1][playerPos.y + move.y1]->Move(move.dir,2);
			Player->Move(move.dir,2);
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
	if (Player != nullptr) Player->Simulate(deltaTime);
	for (auto& i : mapObjects)
		for (auto& j : i)
			if (j != nullptr)j->Simulate(deltaTime);
	for (auto& i : Enemy)
		i->Simulate(deltaTime);

}

void SetBomb();

void simulation()
{
	static double Accumulator;
	static double PrevTime = StartCounter.QuadPart;
	LARGE_INTEGER CurrTime;
	QueryPerformanceCounter(&CurrTime);
	double deltaTime = (CurrTime.QuadPart - PrevTime)/Frequency.QuadPart;
	PrevTime = CurrTime.QuadPart;
	Accumulator += deltaTime;

	CameraSimulation(deltaTime);
	GameObjectsSimulation(deltaTime);

     if(Player)MovePlayer();

	//Контроль частоты движений врагов(Numpad 0,1,3,5)|Нажать
	static float con;
	if (static_cast<bool>(GetAsyncKeyState(VK_NUMPAD0))) con = Accumulator;
	if (static_cast<bool>(GetAsyncKeyState(VK_NUMPAD1))) con = 0.1;
	if (static_cast<bool>(GetAsyncKeyState(VK_NUMPAD3))) con = 0.05;
	if (static_cast<bool>(GetAsyncKeyState(VK_NUMPAD5))) con = 0.5;

	if (Accumulator >= con)
	{
		for (int i = 0; i < 3; i++)
			MoveEnemy(Enemy[i]);
		Accumulator = 0;
	}
	glutPostRedisplay();
}