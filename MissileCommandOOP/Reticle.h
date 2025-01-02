#pragma once
#include <vector>
#include "Play.h"
#include "GameObject.h"

/*
class MissileBase;

class Reticle : public GameObject
{
public:
	void Simulate(float elapsedTime) override;
	void Draw() override;

private:
	MissileBase* GetClosestMissileBase(Play::Point2D targetPosition) const;

	bool fired = false;
};

*/

namespace Reticle
{
	using namespace Play;
	using namespace std;

	static bool LBM_PRESSED = false;

	extern void simulate(GameObject* reticle, GameStateManager* manager, float elapsedTime);
	extern void draw(vector<GameObject*> reticles);
	
	extern GameObject* getClosestMissileBase(Play::Point2D targetPosition, vector<GameObject*> bases, GameObject* reticle);

	/*
	void draw(GameObject& reticle)
	{
		const int reticleHalfSize = 2; // half (size - 1)
		Play::DrawLine(reticle.GetPosition() + Play::Vector2D(-reticleHalfSize, 0), reticle.GetPosition() + Play::Vector2D(reticleHalfSize, 0), Play::cGreen);
		Play::DrawLine(reticle.GetPosition() + Play::Vector2D(0, reticleHalfSize), reticle.GetPosition() + Play::Vector2D(0, -reticleHalfSize), Play::cGreen);
	}
	*/

	/*
	GameObject* getClosestMissileBase()
	{
		return nullptr;
	}
	*/
}