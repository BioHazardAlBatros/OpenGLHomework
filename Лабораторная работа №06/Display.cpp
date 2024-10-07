#include "Display.h"

void display(void)
{
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	MainCamera.Apply();
	
	MainLight.Apply();
	
	//for (GraphicObject& curr : DrawQueue)
	//{
	//	curr.draw();
	//}
	planeGraphicObject.draw();
	for (auto& i : mapObjects)
		for (auto& j : i)
			if(j!=nullptr) j->Draw();
	glutSwapBuffers();

	char temp[80];
	int FPS = getFPS();
	sprintf_s(temp, "FPS[%d],Camera : %.2f %.2f", FPS, MainCamera.GetAngle().x, MainCamera.GetAngle().y);
	glutSetWindowTitle(temp);
};
