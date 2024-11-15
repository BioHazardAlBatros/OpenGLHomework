#include "Decal.h"

Decal::Decal(glm::ivec2 decalPos)
{
	this->position = decalPos;
	this->graphicObject.SetMaterial(Decal::decalTexture);
	this->graphicObject.SetMesh(Decal::decalMesh);
	this->graphicObject.SetPosition({ this->position.x,-0.5,this->position.y });
}
Decal::Decal()
{
	this->position = { 0,0 };
	this->graphicObject.SetPosition({ this->position.x,-0.5,this->position.y });
}
std::shared_ptr<Mesh> Decal::decalMesh = nullptr;
std::shared_ptr<PhongMaterialWithTexture> Decal::decalTexture = nullptr;
int Decal::lastIndex = 0;

void Decal::Init()
{
	Decal::decalMesh = std::make_unique<Mesh>(R"(assets/models/Decal.obj)");
	Decal::decalTexture = std::make_unique<PhongMaterialWithTexture>(R"(assets/textures/decal.png)", 0);
}
void Decal::Draw()
{
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	glPolygonOffset(-1, -3);
	this->graphicObject.Draw();
	glDisable(GL_BLEND);
	glDisable(GL_POLYGON_OFFSET_FILL);

}