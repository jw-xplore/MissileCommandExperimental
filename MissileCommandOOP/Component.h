#pragma once

#include "Constants.h"

class ComponentBase
{
public:
	ComponentBase(int id, EObjectType type);
	virtual ~ComponentBase() {}

	//int GetId();

private:
	int id;
	EObjectType type;
};