#include <windows.h>
#include <vector>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GraphicObject.h"

//					  Вектор цветов		0.Белый		  1.Синий	   2.Красный	 3.Желтый	   4.Фиолетовый
std::vector<glm::vec3> teapotColors{ {1.0,1.0,1.0},{0.0,0.0,1.0},{1.0,0.0,0.0},{1.0,1.0,0.0}, {1.0,0.0,1.0} };
//					 Вектор с названиями цветов
std::vector<const char*> colorsName{ "white","blue","red","yellow","purple" };
//Количество доступных цветов
const int colorsAmount = teapotColors.size();
//Текущий индекс в векторе цветов
int colorsIndex;
//Цвет чайника
glm::vec3 currentColor(teapotColors[0]);



std::vector<GraphicObject> DrawQueue;
void interpolate(glm::vec3& oldColor, glm::vec3& newColor, glm::vec3& currentColor)
{
	static float oldAlpha = 1.0;
	//Вычисление новой прозрачности
		   float newAlpha = 1.0 - oldAlpha;
	// Вывод информации о текущем состоянии
	std::cout << colorsName[colorsIndex]<< "->"<<colorsName[(colorsIndex + 1) % colorsAmount]
			  << " completed - " << (newAlpha) * 100 << '%' << std::endl;
	//вычисление нового цвета по формуле
	//текущийЦвет.канал = стараяПрозрачность*старыйЦвет.канал + (1.0-стараяПрозрачность)*новыйЦвет.канал
	currentColor.r = oldAlpha * oldColor.r + newAlpha * newColor.r;
	currentColor.g = oldAlpha * oldColor.g + newAlpha * newColor.g;
	currentColor.b = oldAlpha * oldColor.b + newAlpha * newColor.b;
	oldAlpha -= 0.01;
	//Интерполяция к следующему цвету, если предыдущий цвет полностью интерполировался к новому.
	if (oldAlpha < 0.0) { oldAlpha =1.0; colorsIndex = (colorsIndex + 1) % colorsAmount; }
	return;
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
	gluLookAt(10, 15,17.5, 0, 0,0, 0, 1, 0);

	
	for (GraphicObject& curr : DrawQueue)
			curr.draw();
	// смена переднего и заднего буферов
	glutSwapBuffers();
	//GLfloat modelMatrix0[16]{ -1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,-1.0,0.0,4.0,0.0,0.0,1.0};
	//GLfloat modelMatrix1[16]{  1.0,0.0,0.0,0.0, 0.0,1.0,0.0,0.0, 0.0,0.0,1.0,0.0,-4.0,0.0,0.0,1.0};
	////GLFloat MatrixFirst[16] =  {}
	//glColor3f(currentColor.r, currentColor.g, currentColor.b);
	//glPushMatrix();
	//glMultMatrixf(modelMatrix0);
	//glutWireTeapot(1.0);
	//glPopMatrix();
	//glPushMatrix();
	//glColor3f(teapotColors[2].r, teapotColors[2].g, teapotColors[2].b);
	//glPushMatrix();
	//glMultMatrixf(modelMatrix1);
	//glutWireTeapot(1.0);
	//glPopMatrix();
	
};

// функция вызывается каждые 20 мс
void simulation(int value)
{
	//interpolate(teapotColors[colorsIndex], teapotColors[(colorsIndex+1)%colorsAmount], currentColor);
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(20, simulation, 0);
};

// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", key);
};


void main(int argc, char** argv)
{
	//setlocale(LC_ALL, "ru");
	//GraphicObject firstTeapot ({ -4.0,0.0,0.0 }, teapotColors[0], 0.0);
	//GraphicObject secondTeapot({  0.0,0.0,4.0 }, teapotColors[1], 90.0);
	//GraphicObject thirdTeapot ({  4.0,0.0,0.0 }, teapotColors[2], 180.0);
	//GraphicObject fourthTeapot({  0.0,0.0,-4.0}, teapotColors[3], 270.0);
	DrawQueue.push_back(GraphicObject({ -4.0,0.0,0.0  }, teapotColors[0], 0.0));
	DrawQueue.push_back(GraphicObject({  0.0,0.0,4.0  }, teapotColors[1], 90.0));
	DrawQueue.push_back(GraphicObject({  4.0,0.0,0.0  }, teapotColors[2], 180.0));
	DrawQueue.push_back(GraphicObject({  0.0,0.0,-4.0 }, teapotColors[3], 270.0));

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
	glutCreateWindow("Laba_03");

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