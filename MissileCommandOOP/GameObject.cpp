#include "GameObject.h"

GameObject::GameObject(EObjectType type) : gameStateManager(nullptr), scheduledDelete(false)
{
	this->type = type;
}

GameObject::~GameObject()
{
	// override in subclass
}

Play::Point2D GameObject::GetPosition() const
{
	return this->position;
}

void GameObject::SetPosition(Play::Point2D const& newPosition)
{
	this->position = newPosition;
}

void GameObject::ScheduleDelete()
{
	this->scheduledDelete = true;
}

/*
void GameObject::Simulate(float elapsedTime)
{
	// override in subclass
}
*/

void GameObject::SetId(int id)
{
	if (this->id == -1 && id > 0)
		this->id = id;
}

int GameObject::GetId()
{
	return id;
}

EObjectType GameObject::GetType()
{
	return type;
}
