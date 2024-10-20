#include <windows.h>
#include <vector>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//					  ������ ������		0.�����		  1.�����	   2.�������	 3.������	   4.����������
std::vector<glm::vec3> teapotColors{ {1.0,1.0,1.0},{0.0,0.0,1.0},{1.0,0.0,0.0},{1.0,1.0,0.0}, {1.0,0.0,1.0} };
//					 ������ � ���������� ������
std::vector<const char*> colorsName{ "white","blue","red","yellow","purple" };
//���������� ��������� ������
const int colorsAmount = teapotColors.size();
//������� ������ � ������� ������
int colorsIndex;
//���� �������
glm::vec3 currentColor(teapotColors[0]);

void interpolate(glm::vec3& oldColor, glm::vec3& newColor, glm::vec3& currentColor)
{
	static float oldAlpha = 1.0;
	//���������� ����� ������������
		   float newAlpha = 1.0 - oldAlpha;
	// ����� ���������� � ������� ���������
	std::cout << colorsName[colorsIndex]<< "->"<<colorsName[(colorsIndex + 1) % colorsAmount]
			  << " completed - " << (newAlpha) * 100 << '%' << std::endl;
	//���������� ������ ����� �� �������
	//�����������.����� = ������������������*����������.����� + (1.0-������������������)*���������.�����
	currentColor.r = oldAlpha * oldColor.r + newAlpha * newColor.r;
	currentColor.g = oldAlpha * oldColor.g + newAlpha * newColor.g;
	currentColor.b = oldAlpha * oldColor.b + newAlpha * newColor.b;
	oldAlpha -= 0.01;
	//������������ � ���������� �����, ���� ���������� ���� ��������� ���������������� � ������.
	if (oldAlpha < 0.0) { oldAlpha =1.0; colorsIndex = (colorsIndex + 1) % colorsAmount; }
	return;
};
// �������, ���������� ��� ��������� �������� ����
void reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void display(void)
{
	// �������� ����� ����� � ����� �������
	glClearColor(0.22, 0.88, 0.11, 1.0); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);

	// ������������� ������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, -5, 7.5, 0, 0,0, 0, 1, 0);

	// ������� ������ - ������� (1,0,0) ������
	glColor3f(currentColor.r, currentColor.g, currentColor.b);
	glutWireTeapot(1.0);

	// ����� ��������� � ������� �������
	glutSwapBuffers();
};

// ������� ���������� ������ 20 ��
void simulation(int value)
{
	//������� ����� ����� �������
	//���� � �������� ������� ������� �� ������� (colorsIndex+1) �� colorsAmount, �� ������� �� ������ �� ������� �������
	interpolate(teapotColors[colorsIndex], teapotColors[(colorsIndex+1)%colorsAmount], currentColor);
	
	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
															//	colorsIndex = min(colorsAmount, colorsIndex++);
	// ��� �� ������� ����� ������� ��� ��� ����� 20 ��
	glutTimerFunc(20, simulation, 0);
};

// ������� ��������� ������� ������
void keyboardFunc(unsigned char key, int x, int y)
{
	if (key == 'r' || key == 'R') { colorsIndex = 3; }
	if (key == 'g' || key == 'G') { colorsIndex = 2; }
	printf("Key code is %i\n", key);
};

void main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");

	// ������������� ���������� GLUT
	glutInit(&argc, argv);	
	// ������������� ������� (������ ������)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// �������� ����:
	// 1. ������������� ������� ����� ���� ����
	glutInitWindowPosition(200, 200);
	// 2. ������������� ������ ����
	glutInitWindowSize(800, 600);
	// 3. ������� ����
	glutCreateWindow("Laba_02");

	// ��������� ������� ��������� ������
	// ������������� �������, ������� ����� ���������� ��� ����������� ����
	glutDisplayFunc(display);
	// ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
	glutReshapeFunc(reshape);
	// ������������� �������, ������� ����� ������� ����� 20 ��
	glutTimerFunc(20, simulation, 0);
	// ������������� �������, ������� ����� ���������� ��� ������� �� �������
	glutKeyboardFunc(keyboardFunc);

	// �������� ���� ��������� ��������� ��
	glutMainLoop();
};