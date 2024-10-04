#include "Display.h"


void display(void)
{
	glClearColor(0.22, 0.22, 0.11, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	MainCamera.Apply();

	for (GraphicObject& curr : DrawQueue)
	{
		curr.draw();
	}
	glutSwapBuffers();
	char temp[80];
	int FPS = getFPS();
	sprintf_s(temp, "FPS[%d],Camera : %.2f %.2f", FPS, MainCamera.GetAngle().x, MainCamera.GetAngle().y);
	glutSetWindowTitle(temp);
};
