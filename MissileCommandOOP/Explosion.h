#pragma once
//#include "GameStateManager.h"
#include "GameObject.h"
#include "Play.h"

namespace Explosion
{
	//using namespace std;
	using namespace Play;

	struct ExplosionComponent;

	struct ExplosionComponent
	{
		Point2D position;
		float currentRadius;
		float maxRadius;
		int alternateColour;
		bool hasExploded;

		//ExplosionComponent();
	};

	extern void simulate(std::vector<GameObject*> gameObjects, std::map<int, ExplosionComponent>* explosions, GameStateManager* manager, float elapsedTime);
	extern void draw(std::map<int, ExplosionComponent>* explosions);

	//extern void explode(GameObject* gameObject, ExplosionComponent* explosion, map<GameObject*, int>* healthComponents);
}



/*
#include "GameObject.h"

class Explosion : public GameObject
{
public:
	Explosion(Play::Point2D position);

	void Simulate(float elapsedTime) override;

	void Draw() override;

private:
	float currentRadius;
	float maxRadius;
	int alternateColour;

	void Explode();

	bool hasExploded;
};
*/