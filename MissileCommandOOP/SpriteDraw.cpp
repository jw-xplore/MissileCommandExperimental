#include "SpriteDraw.h"
#include "Play.h"

void SpriteDraw::drawSprite(vector<GameObject*> gameObjects, map<int, const char*> sprites)
{
	int id;

	for (int i = 0; i < gameObjects.size(); i++)
	{
		id = gameObjects[i]->GetId();
		DrawSprite(sprites.at(id), gameObjects[i]->GetPosition(), 0);
	}
}