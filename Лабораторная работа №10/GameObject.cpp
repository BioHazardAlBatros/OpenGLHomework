#include "GameObject.h"

GameObject::GameObject()
{
	this->dir = MoveDirection::STOP;
	this->lastdir = this->dir;
	this->speed = 3.0f;
	this->progress = 0.0f;
	this->SetPosition({ 0,0 });
}
int GameObject::GetLastDir()
{
	return rand() % 4;
//THIS IS BROKEN :D
	if (this->lastdir == MoveDirection::STOP)
		this->lastdir = static_cast<MoveDirection>((rand() % 4) +1);
	std::cout << static_cast<int>(this->lastdir)-1<< ' ' << static_cast<int>(this->dir)<<' ';
	return static_cast<int>(this->lastdir)-1;
//THIS IS BROKEN D:
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
		this->lastdir = this->dir;//<- BROKEN 
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