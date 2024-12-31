#include "GameObject.h"

GameObject::GameObject() : gameStateManager(nullptr), scheduledDelete(false)
{
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

void GameObject::Simulate(float elapsedTime)
{
	// override in subclass
}
