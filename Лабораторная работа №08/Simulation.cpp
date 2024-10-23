#include "Simulation.h"
#include <iostream>

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

void simulation()
{
	static double PrevTime = StartCounter.QuadPart;
	LARGE_INTEGER CurrTime;
	QueryPerformanceCounter(&CurrTime);
	double deltaTime = (CurrTime.QuadPart - PrevTime)/Frequency.QuadPart;
	PrevTime = CurrTime.QuadPart;

	static float rotateSpeed = 90.0;
	static float leanSpeed = 1.f;

	if (static_cast<bool>(GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)))  MainCamera.RotateLeftRight(rotateSpeed * deltaTime);
	if (static_cast<bool>(GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT))) MainCamera.RotateLeftRight(-rotateSpeed * deltaTime);
	if (static_cast<bool>(GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)))	 MainCamera.RotateUpDown(2 * rotateSpeed * deltaTime);
	if (static_cast<bool>(GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)))  MainCamera.RotateUpDown(-2 * rotateSpeed * deltaTime);
	if (static_cast<bool>(GetAsyncKeyState(VK_SUBTRACT))) MainCamera.ZoomOutin(40 * deltaTime);
	if (static_cast<bool>(GetAsyncKeyState(VK_ADD)))	  MainCamera.ZoomOutin(-40 * deltaTime);
	if (static_cast<bool>(GetAsyncKeyState(0x45)))		  MainCamera.LeanLeftRight(-leanSpeed * deltaTime);
	if (static_cast<bool>(GetAsyncKeyState(0x51)))	      MainCamera.LeanLeftRight(leanSpeed * deltaTime);

	/*for (GraphicObject& i : DrawQueue)
	{
		i.SetAngle(i.GetAngle() + 2.5);
	}*/
	glutPostRedisplay();
}