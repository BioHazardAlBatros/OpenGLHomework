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

void KillPlayer()
{
	Player.reset();
	system("cls");
	std::printf("\tChange the world... My final message... Goodbye.");
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
	if (!entity->isMoving() && pathMap[entityPos.x + Moves[PickMove].x1][entityPos.y + Moves[PickMove].y1] == 0)
	{
		entity->Move(Moves[PickMove].dir, 3);
		std::swap(pathMap[entityPos.x + Moves[PickMove].x1][entityPos.y + Moves[PickMove].y1],
			pathMap[entityPos.x + 10][entityPos.y + 10]);
		std::swap(mapObjects[entityPos.x + Moves[PickMove].x1][entityPos.y + Moves[PickMove].y1],
			mapObjects[entityPos.x + 10][entityPos.y + 10]);
	}
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

	if (pathMap[playerPos.x + 10][playerPos.y + 10] == 4)
	{
		KillPlayer();
		return;
	}

	for (auto move : Moves)
	{
		if (static_cast<bool>(GetAsyncKeyState(move.key)) && !Player->isMoving() && pathMap[playerPos.x + move.x1][playerPos.y + move.y1] <= 1)
			if (pathMap[playerPos.x + move.x1][playerPos.y + move.y1] == 1 && pathMap[playerPos.x + move.x2][playerPos.y + move.y2] == 0)
			{
				mapObjects[playerPos.x + move.x1][playerPos.y + move.y1]->Move(move.dir, 2);
				Player->Move(move.dir, 2);
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
	if (Player) Player->Simulate(deltaTime);
	for (auto& i : mapObjects)
		for (auto& j : i)
			if (j != nullptr)j->Simulate(deltaTime);
}
void DestroyIfPossible(glm::ivec2 pos, glm::ivec2 displacement, bool Decrease)
{
	if (Decrease) displacement *= -1;

	if (Player)
	{
		glm::ivec2 realPos{ pos.x - 10,pos.y - 10 };
		glm::ivec2 playerPos = Player->GetPosition();
		if ((glm::ivec2({ realPos.x + displacement.x,realPos.y + displacement.y }) == playerPos && pathMap[pos.x][pos.y] == 0)
			|| glm::ivec2({ realPos.x,realPos.y }) == playerPos)
		{
			KillPlayer();
			return;
		}
	}

	if (pathMap[pos.x][pos.y] == 1 || pathMap[pos.x][pos.y] == 4)
	{
		//Если в клетке враг, то также уничтожаем ссылку на объект в массиве указателей на врага 
		for (int i = 0; i < 3; i++)
			if (Enemy[i] && Enemy[i] == mapObjects[pos.x][pos.y])
			{
				Enemy[i].reset();
				break;
			}
		mapObjects[pos.x][pos.y].reset();
		pathMap[pos.x][pos.y] = 0;
		return;
	}
	if (pathMap[pos.x][pos.y] == 0 &&
		(pathMap[pos.x + displacement.x][pos.y + displacement.y] == 1 || pathMap[pos.x + displacement.x][pos.y + displacement.y] == 4))
	{
		//Если в клетке враг, то также уничтожаем ссылку на объект в массиве указателей на врага 
		for (int i = 0; i < 3; i++)
			if (Enemy[i] && Enemy[i] == mapObjects[pos.x + displacement.x][pos.y + displacement.y])
			{
				Enemy[i].reset();
				break;
			}
		mapObjects[pos.x + displacement.x][pos.y + displacement.y].reset();
		pathMap[pos.x + displacement.x][pos.y + displacement.y] = 0;
	}
	return;
}

void BombSimulation(double currentTime)
{
	static double timeToActivate = 5.0 * Frequency.QuadPart;
	static LARGE_INTEGER placementTime;
	static glm::ivec2 bombPos;
	static bool isBombSet = false;
	if (Player && !Player->isMoving() && !isBombSet && (GetAsyncKeyState(VK_SPACE)) & 0x8000)
	{
		isBombSet = true;
		QueryPerformanceCounter(&placementTime);
		bombPos = { Player->GetPosition().x + 10, Player->GetPosition().y + 10 };
		mapObjects[bombPos.x][bombPos.y] = gameObjFactory.Create(GameObjectFactory::BOMB, bombPos - 10);
		pathMap[bombPos.x][bombPos.y] = 5;
	}

	//Состояние таймера
	//std::printf("%f %f\n", currentTime - placementTime.QuadPart, secondsToActivate * Frequency.QuadPart);
	if (isBombSet && currentTime - placementTime.QuadPart >= timeToActivate)
	{
		isBombSet = false;
		mapObjects[bombPos.x][bombPos.y].reset();
		pathMap[bombPos.x][bombPos.y] = 0;

		//Состояние карт
		//for (int i = 0; i < 21; i++) {
		//	for (int j = 0; j < 21; j++)
		//		std::cout << pathMap[j][i] << ' ';
		//	std::cout << std::endl;
		//}
		//std::cout << std::endl;
		//for (int i = 0; i < 21; i++) {
		//	for (int j = 0; j < 21; j++)
		//		std::cout << mapObjects[j][i] << ' ';
		//	std::cout << std::endl;
		//}

		DestroyIfPossible({ bombPos.x - 1,bombPos.y }, { 1,0 }, true);//Клетки слева
		DestroyIfPossible({ bombPos.x + 1,bombPos.y }, { 1,0 }, false);//Клетки справа
		DestroyIfPossible({ bombPos.x, bombPos.y - 1 }, { 0,1 }, true);//Клетки снизу
		DestroyIfPossible({ bombPos.x, bombPos.y + 1 }, { 0,1 }, false);//Клетки сверху
	}

}

void simulation()
{
	static double PrevTime = StartCounter.QuadPart;
	LARGE_INTEGER CurrTime;
	QueryPerformanceCounter(&CurrTime);
	double deltaTime = (CurrTime.QuadPart - PrevTime) / Frequency.QuadPart;
	PrevTime = CurrTime.QuadPart;

	CameraSimulation(deltaTime);
	GameObjectsSimulation(deltaTime);

	if (Player)MovePlayer();
	BombSimulation(CurrTime.QuadPart);

	//Контроль движений врагов|Зажать NUM8
	if (!static_cast<bool>(GetAsyncKeyState(VK_NUMPAD8)))
	{
		for (int i = 0; i < 3; i++)
			if (Enemy[i]) MoveEnemy(Enemy[i]);
	}
	glutPostRedisplay();
}