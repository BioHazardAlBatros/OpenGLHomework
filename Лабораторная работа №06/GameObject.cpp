#include "GameObject.h"
//class GameObject
//{
//private:
//	glm::ivec2 position;
//	GraphicObject graphicObject;
//public:

//	
//};

GameObject::GameObject()
{
	this->SetPosition({ 0,0 });
}

glm::ivec2 GameObject::GetPosition()
{
	return this->position;
}
void GameObject::SetGraphicObject(const GraphicObject& object)
{
	this->graphicObject = object;
	this->graphicObject.SetPosition({ this->position.x,0,this->position.y });
//	this->graphicObject.SetPosition({this->position.x, this->position.y,0});
}
void GameObject::SetPosition(int x, int y)
{
	this->position = { x,y };
}
void GameObject::SetPosition(glm::ivec2 pos)
{
	this->position = pos;
}
void GameObject::Draw()
{
//	this->graphicObject.SetPosition({ this->position.x,0,this->position.y });
	this->graphicObject.draw();
}