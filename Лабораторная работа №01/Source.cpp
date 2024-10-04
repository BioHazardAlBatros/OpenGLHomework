#include <windows.h>

#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

// ���������� ������������ ���� ����������� ����������
using namespace std;


struct Color
	{
	float R, G, B;
	Color() :R(1.0), G(0.0), B(0.0) {};
	Color(float r, float g, float b) :R(r), G(g), B(b) {};
	bool operator==(const Color& other) { return (this->R == other.R) && (this->G == other.G) && (this->B == other.G); };
	};
					//Black				White		  Blue			Red			Purple
Color ArrayOfColors[]{ {0.0,0.0, 0.0},{1.0,1.0,1.0},{0.0,0.0,1.0},{1.0,0.0,0.0},{1.0,0.0,1.0} };
const int SizeOfColors = 5;
int ColorsPos;
int Multi=0;
const float delta = 0.01;
//���� �������
Color CurrentColor{ ArrayOfColors[0] };

void interpolate(Color& CurrentColor,Color& OldColor, Color& NewColor)
{
	static float oldAlpha = 1.0;
	//���������� ����� ������������
	float newAlpha = 1.0 - oldAlpha;
	// ����� ���������� � ������� ���������
	//���������� ������ ����� �� �������
	//�����������.����� = ������������������*����������.����� + (1.0-������������������)*���������.�����
	CurrentColor.R = oldAlpha * OldColor.R + newAlpha * NewColor.R;
	CurrentColor.G = oldAlpha * OldColor.G + newAlpha * NewColor.G;
	CurrentColor.B = oldAlpha * OldColor.B + newAlpha * NewColor.B;
	oldAlpha -= 0.01;
	//������������ � ���������� �����, ���� ���������� ���� ��������� ���������������� � ������.
	if (oldAlpha < 0.0) { oldAlpha = 1.0; ColorsPos = (ColorsPos+ 1) % SizeOfColors; }
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
	//5,-16
	gluLookAt(5, -5, 7.5, 0, 0,0, 0, 1, 0);

	// ������� ������ - ������� (1,0,0) ������
	glColor3f(CurrentColor.R, CurrentColor.G, CurrentColor.B);
	glutWireTeapot(1.0);

	// ����� ��������� � ������� �������
	glutSwapBuffers();
};

// ������� ���������� ������ 20 ��
void simulation(int value)
{
	//static int counter = 0;
	interpolate(CurrentColor, ArrayOfColors[ColorsPos], ArrayOfColors[(ColorsPos+1)%SizeOfColors]);
	/*if (counter >= 50)
	{
		counter = 0;
		if ((ColorsPos++) >= SizeOfColors) ColorsPos = 0;
	}
	counter++;*/

	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
															//	ColorsPos = min(SizeOfColors, ColorsPos++);
	// ��� �� ������� ����� ������� ��� ��� ����� 20 ��
	glutTimerFunc(20, simulation, 0);
};

// ������� ��������� ������� ������
void keyboardFunc(unsigned char key, int x, int y)
{
	if (key == 'a') { Multi++; }
	if (key == 'z') { Multi--; }
	if (key == 'r' || key == 'R') { ColorsPos = 3; }
	if (key == 'g' || key == 'G') { ColorsPos = 2; }
	//if (key == ' ') ColorsPos = 0;
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
	glutCreateWindow("Laba_01");

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
//#include <Windows.h>
//#include <GL\glew.h>
//#include <GL\freeglut.h>
//#include <iostream>
//#include <chrono>
//const float length = 30;
//static bool Update = false;
//const double frame_delay = 1.0 / 60.0; // 60 FPS
//double last_render = 0;
//GLdouble First[]{ -10,-10 }, Second[]{ 0,0 };
//
//double GetTime()
//{
//	using Duration = std::chrono::duration<double>;
//	return std::chrono::duration_cast<Duration>(
//		std::chrono::high_resolution_clock::now().time_since_epoch()
//	).count();
//}
//void SpecialButtons(int key, int x, int y)
//{
//	switch (key) {
//
//	case GLUT_KEY_LEFT:  Second[0] -= .5;  break;
//	case GLUT_KEY_RIGHT: Second[0] += .5;  break;
//	case GLUT_KEY_UP:	 Second[1] += .5;  break;
//	case GLUT_KEY_DOWN:  Second[1] -= .5;  break;
//	default:	         break;
//	}
//	//const double current_time = GetTime();
//	//if ((current_time - last_render) > frame_delay)
//	//{
//	//	last_render = current_time;
//		glutPostRedisplay();
//	//}
//}
//void Buttons(unsigned char key, int x, int y)
//{
//	switch (key)
//	{
//	case 'a':			First[0] -= .1; break;
//	case 'd':			First[0] += .1; break;
//	case 's':			First[1] += .1; break;
//	case 'w':			First[1] -= .1; break;
//	default:			break;
//	}
////	const double current_time = GetTime();
//	//if ((current_time - last_render) > frame_delay)
//	//{
//		//last_render = current_time;
//		glutPostRedisplay();
//	//}
//}
//void DisplayTriangle()
//{
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glBegin(GL_TRIANGLES);
//		glColor3f(sin(First[0]), cos(First[1]), 0.9f);
//		//glLineWidth(200.0);
//		glPointSize(100);
//		glVertex2f(First[1] * sin(First[0]) + Second[0], First[1] * cos(First[0]) + Second[1]);
//		glVertex2f(Second[0], Second[1]);
//		//glColor3f(sin(First[1]), cos(First[0]), 0.9f);
//		glVertex2f(Second[0], -Second[1] - 1);
//		//glVertex2f(First[1] * -sin(First[0]) + Second[0], (First[1] * -cos(First[0]) + Second[1]));
//		glEnd();
//		glutSwapBuffers();
//}
//void DisplayLine() 
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glBegin(GL_LINES);
//	glColor3f(sin(First[0]), cos(First[1]), 0.9f);
//	glLineWidth(200.0);
//	glVertex2f(First[1]*sin(First[0])+Second[0], First[1]*cos(First[0]) + Second[1]);
//	glVertex2f(Second[0], Second[1]);
//	glColor3f(sin(First[1]), cos(First[0]), 0.9f);
//	glVertex2f(Second[0], -Second[1]);
//	glVertex2f(First[1] * -sin(First[0]) + Second[0], (First[1] * -cos(First[0]) + Second[1]));
//	glEnd();
//	glutSwapBuffers();
//}
//void display()
//{
//	//����� �����
//	if (Update)return;
//	for (float i = 0; i < length; i += 0.005)
//	{
//		glBegin(GL_POINTS);
//		glPointSize(100);
//		//��������� ��������
//			glColor3f(1.0f, 1.0f, 1.0f);
//				glVertex2f( i, cos(i));
//				glVertex2f(-i, cos(-i));
//			glColor3f(1.0f, 0.0f, 0.0f);
//				glVertex2f(i, i);
//				glVertex2f(-i, -i);
//			glColor3f(0.0f, 0.0f, 1.0f);
//				glVertex2f(i, atan(i));
//				glVertex2f(-i, atan(-i));
//			glColor3f(0.0f, 1.0f, 0.0f);
//				glVertex2f(16 * pow(sin(i), 3), 13 * cos(i) - 5 * cos(2 * i) - 2 * cos(3 * i) - cos(4 * i));
//				glVertex2f(16 * pow(sin(-i), 3), 13 * cos(-i) - 5 * cos(2 * (-i)) - 2 * cos(3 * (-i)) - cos(4 * (-i)));
//			glColor3f(0.75f, 0.5f, 0.5f);
//				glVertex2f(i,int(i));
//				glVertex2f(-i, int(-i));
//			glColor3f(0.25f, 0.25f, 0.75f);
//				glVertex2f(i, tan(i));
//				glVertex2f(-i, tan(-i));
//			//��������� ���������
//			glEnd();
//			//����� ������������� �����
//			glutSwapBuffers();
//	}
//	Update = true;
//	}
//
////rofls
//
//int main(int argc, char* argv[]) {
//
//	// ������������� glut
//	glutInit(&argc, argv);
//	// ������ ����
//	glutInitWindowSize(1280, 720);
//	// �������� ����
//	glutCreateWindow("FortniteClient-Win64-Shipping.exe");
//	glMatrixMode(GL_PROJECTION);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	//���������� ��������
//	//glScalef(0.3, 0.55, 0.1);
//	//glScalef(0.03, 0.055, 0.1);
//	glutKeyboardFunc(Buttons);
//	glutSpecialFunc(SpecialButtons);
//	glutDisplayFunc(display);
//	glutMainLoop();
//	return 0;
//}
