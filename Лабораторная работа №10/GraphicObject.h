#pragma once
#include <Windows.h>
#include <memory>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"
#include "Mesh.h"

class GraphicObject
{
private:
	std::shared_ptr<Material> material;
	std::shared_ptr<Mesh> mesh;
	glm::vec3 position;
	glm::vec3 color;
	float angle;
	GLfloat modelMatrix[16];
	void recalculateMatrix();
public:
	GraphicObject();
	GraphicObject(glm::vec3 pos,glm::vec3 color,float angle);
	GraphicObject(glm::vec3 pos, glm::vec3 color, float angle,std::shared_ptr<Material> mat);
	void SetPosition(glm::vec3 newPosition);
	glm::vec3 GetPosition();

	void SetMaterial(std::shared_ptr<Material> mat);
	void SetMesh(std::shared_ptr<Mesh> mesh);

	void SetAngle(float newAngle);
	float GetAngle();

	void SetColor(glm::vec3 newColor);
	glm::vec3 GetColor();

	void Draw();
};