#pragma once
#include "Structure.h"
#include "Play.h";

/*
class MissileBase : public Structure
{
public:
	MissileBase();

	void Draw() override;

	void Simulate(float elapsedTime) override;

	void FireMissile(Play::Point2D target);

private:
	int maxMissiles;
	int missileCount;
	float missileSpeed;
	float timeSinceReload;
	float reloadTime;
};
*/

namespace MissileBase
{
	using namespace std;
	using namespace Play;

	struct MissileBaseComponent
	{
		int maxMissiles = 10;
		int missileCount = maxMissiles;
		float missileSpeed = 50;
		float timeSinceReload = 0;
		float reloadTime = 1;
	};

	extern void simulate(vector<GameObject*> bases, map<int, MissileBaseComponent> componets, float elapsedTime);

	extern void fireMissile(GameObject* base, MissileBaseComponent* component, GameStateManager* manager, Point2D target);
}