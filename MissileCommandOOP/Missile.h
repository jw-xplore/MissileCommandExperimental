#pragma once
#include <map>
#include "Destroyable.h"

namespace Missile
{
	using namespace std;
	using namespace Play;

	struct MissileComponent
	{
		Play::Colour colour;
		Play::Point2D origin;
		Play::Point2D target;
		float distanceTravelled;
		int alternateColour;
		float speed;

		MissileComponent();
		MissileComponent(Play::Point2D origin, Play::Point2D target, Play::Colour colour, float speed);
		//Vector2D GetTravellingDirection();
	};

	extern void simulate(vector<GameObject*> gameObjects, map<int, MissileComponent> missiles, float elapsedTime);
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

