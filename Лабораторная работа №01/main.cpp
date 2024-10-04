#include <windows.h>

#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

// используем пространство имен стандартной библиотеки
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
int Multi = 0;
const float delta = 0.01;
//Цвет чайника
Color CurrentColor{ ArrayOfColors[1] };

bool interpolate(Color& OldColor, Color& ColorToInterpolate)
{
	//static float alpha = 1.0; 
	//static Color SavedColor = CurrentColor;

	if ((abs(ColorToInterpolate.R - OldColor.R) < delta)
		&& (abs(ColorToInterpolate.G - OldColor.G) < delta)
		&& (abs(ColorToInterpolate.B - OldColor.B) < delta))	return false;

	//if (OldColor == ColorToInterpolate) return false;
	//if (alpha < 0.0) { alpha = 1.0; SavedColor = ColorToInterpolate; }

	//OldColor.R = alpha * SavedColor.R + (1-alpha)*ColorToInterpolate.R;
	//OldColor.G = alpha * SavedColor.G + (1 - alpha) * ColorToInterpolate.B;
	//OldColor.B = alpha * SavedColor.B + (1 - alpha) * ColorToInterpolate.G;
	//alpha -= 0.05;
	//if (alpha < 0.0) alpha = 1.0;
	OldColor.R += (1 - (ColorToInterpolate.R < OldColor.R) * 2) * 0.01 * pow(10, Multi);//alpha * OldColor.R + (1 - alpha) * ColorToInterpolate.R;//(ColorToInterpolate.R < OldColor.R)? -0.005: 0.005;
	OldColor.G += (1 - (ColorToInterpolate.G < OldColor.G) * 2) * 0.01 * pow(10, Multi);//alpha * OldColor.B + (1 - alpha) * ColorToInterpolate.B;//(ColorToInterpolate.G < OldColor.G)? -0.005: 0.005;
	OldColor.B += (1 - (ColorToInterpolate.B < OldColor.B) * 2) * 0.01 * pow(10, Multi);//alpha * OldColor.G + (1 - alpha) * ColorToInterpolate.G;//
	std::cout << OldColor.R << ' ' << OldColor.G << ' ' << OldColor.B << std::endl;
	return true;
};
// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void display(void)
{
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.22, 0.88, 0.11, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);

	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//5,-16
	gluLookAt(5, -5, 7.5, 0, 0, 0, 0, 1, 0);

	// выводим объект - красный (1,0,0) чайник
	glColor3f(CurrentColor.R, CurrentColor.G, CurrentColor.B);
	glutWireTeapot(1.0);

	// смена переднего и заднего буферов
	glutSwapBuffers();
};

// функция вызывается каждые 20 мс
void simulation(int value)
{
	//static int counter = 0;
	if (!interpolate(CurrentColor, ArrayOfColors[ColorsPos]))  ColorsPos++;
	if (ColorsPos >= SizeOfColors) ColorsPos = 0;
	/*if (counter >= 50)
	{
		counter = 0;
		if ((ColorsPos++) >= SizeOfColors) ColorsPos = 0;
	}
	counter++;*/

	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	//	ColorsPos = min(SizeOfColors, ColorsPos++);
// эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(20, simulation, 0);
};

// Функция обработки нажатия клавиш
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

	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// СОЗДАНИЕ ОКНА:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(800, 600);
	// 3. создаем окно
	glutCreateWindow("Laba_01");

	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(reshape);
	// устанавливаем функцию, которая будет вызвана через 20 мс
	glutTimerFunc(20, simulation, 0);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(keyboardFunc);

	// основной цикл обработки сообщений ОС
	glutMainLoop();
};
