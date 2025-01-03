#pragma once
#include <map>
#include "Destroyable.h"

namespace Missile
{
	using namespace std;
	using namespace Play;

	struct MissileComponent
	{
		Colour colour;
		Point2D origin;
		Point2D target;
		float distanceTravelled = 0;
		int alternateColour = 0;
		float speed = 0;

		MissileComponent();
		MissileComponent(Play::Point2D origin, Play::Point2D target, Play::Colour colour, float speed);

		Vector2D GetTravellingDirection();
		float GetDistanceFromOriginToTarget() const;
	};

	extern void simulate(vector<GameObject*> gameObjects, map<int, MissileComponent>* missiles, GameStateManager* manager, float elapsedTime);
	extern void draw(map<int, MissileComponent>* missiles);
}

namespace Expl
{
	using namespace std;
	using namespace Play;

	struct ExplosionTest
	{
		Point2D position;
		float currentRadius;
		float maxRadius;
		int alternateColour;
		bool hasExploded;
	};
}

/*
class Missile : public Destroyable
{
public:
	Missile(Play::Point2D origin, Play::Point2D target, Play::Colour colour, float speed);

	void Draw() override;

	void Simulate(float elapsedTime) override;

	Play::Vector2D GetTravellingDirection() const;
	
	float GetDistanceFromOriginToTarget() const;

private:
	Play::Colour colour;
	Play::Point2D origin;
	Play::Point2D target;
	float distanceTravelled;
	int alternateColour;
	float speed;
};
*/

