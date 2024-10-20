#include "Display.h"

void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	MainCamera.Apply();
	MainLight.Apply();
	
	planeGraphicObject.Draw();
	Player->Draw();
	for (auto& i : mapObjects)
		for (auto& j : i)
			if(j!=nullptr) j->Draw();

	glutSwapBuffers();

	char temp[80];
	int FPS = getFPS();
	sprintf_s(temp, "FPS[%d],Camera : %.2f %.2f", FPS, MainCamera.GetAngle().x, MainCamera.GetAngle().y);
	glutSetWindowTitle(temp);
};
