#include "Data.h"
#include "Display.h"
#include "Simulation.h"

#include "GraphicObject.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Mesh.h"

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

void main(int argc, char** argv)
{
	ilInit();
	iluInit();
	ilutInit();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutInitWindowPosition(200, 200);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Laba_08");

	printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
	printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
	printf("GL_VERSION = %s\n\n", glGetString(GL_VERSION));

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		printf("Error: %s\n", glewGetErrorString(err));
	}
	printf("Using GLEW %s\n",glewGetString(GLEW_VERSION));

	initData();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(simulation);
	glutMainLoop();
};