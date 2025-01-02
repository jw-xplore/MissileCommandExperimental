#pragma once

#include <vector>
#include <map>
#include "GameObject.h"

namespace SpriteDraw
{
	using namespace std;

	struct SpriteComponent
	{
		const char* spriteName;
	};

	extern void drawSprite(vector<GameObject*> gameObjects, map<int, const char*> sprites);
}