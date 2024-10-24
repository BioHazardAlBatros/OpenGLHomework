#include "GameObject.h"

GameObject::GameObject()
{
	this->dir = MoveDirection::STOP;
	this->speed = 3.0f;
	this->progress = 0.0f;
	this->SetPosition({ 0,0 });
}

glm::ivec2 GameObject::GetPosition()
{
	return this->position;
}
bool GameObject::isMoving()
{
	return this->dir != MoveDirection::STOP;
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
void GameObject::Move(MoveDirection direction, float speed)
{
	if (this->isMoving()) return;
	this->progress = 0.0;
	this->dir = direction;
	this->speed = speed;
}
void GameObject::Simulate(float deltaTime)
{
	if (this->dir == MoveDirection::STOP) return;
	glm::vec3 pos = this->graphicObject.GetPosition();
	glm::ivec2 playerPos = this->GetPosition();
	if (this->progress > 1.0) 
	{   
		this->dir = MoveDirection::STOP;
		this->SetPosition(round(this->graphicObject.GetPosition().x), round(this->graphicObject.GetPosition().z));
		return;
	}
	switch (this->dir)
	{
	case MoveDirection::LEFT:
		this->graphicObject.SetPosition({ playerPos.x * (1 - this->progress) + (playerPos.x - 1) * (this->progress),pos.y, pos.z });
		break;
	case MoveDirection::RIGHT:
		this->graphicObject.SetPosition({ playerPos.x * (1 - this->progress) + (playerPos.x + 1) * (this->progress),pos.y, pos.z });
		break;
	case MoveDirection::UP:
		this->graphicObject.SetPosition({ pos.x,pos.y, playerPos.y * (1 - this->progress) + (playerPos.y - 1) * (this->progress) });
		break;
	case MoveDirection::DOWN:
		this->graphicObject.SetPosition({ pos.x,pos.y, playerPos.y * (1 - this->progress) + (playerPos.y + 1) * (this->progress) });
		break;
	}
	this->progress += this->speed*deltaTime;
}