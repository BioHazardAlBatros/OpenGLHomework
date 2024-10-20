#include "GameObject.h"

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
}
void GameObject::SetPosition(int x, int y)
{
	this->position = { x,y };
	this->graphicObject.SetPosition({x,0,y});
}
void GameObject::SetPosition(glm::ivec2 pos)
{
	this->position = pos;
	this->graphicObject.SetPosition({ pos.x,0,pos.y });
}
void GameObject::Draw()
{
	this->graphicObject.Draw();
}