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

//void keyboardFunc(unsigned char key, int x, int y)
//{
//	printf("Key code is %i\n", key);
//};

void main(int argc, char** argv)
{
	initData();
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutInitWindowPosition(200, 200);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Laba_08");

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Error: " << glewGetErrorString(err);
	}
	std::cout << "Using GLEW " << glewGetString(GLEW_VERSION)<<'\n';
	if (GLEW_ARB_vertex_buffer_object) {
		printf("VBO is supported");
	};
		
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(simulation);
	glutMainLoop();
};