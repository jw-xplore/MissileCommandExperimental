#include "Reticle.h"
#include "Missile.h"
#include "MissileBase.h"
#include "GameStateManager.h"

void Reticle::Simulate(float elapsedTime)
{
	this->SetPosition(Play::Input::GetMousePos());

	if (Play::Input::GetMouseDown(Play::Input::MouseButton::BUTTON_LEFT) && !this->fired)
	{
		this->fired = true;
		MissileBase* closestBase = this->GetClosestMissileBase(this->GetPosition());
		if (closestBase != nullptr)
		{
			closestBase->FireMissile(this->GetPosition());
		}
	}
	if (!Play::Input::GetMouseDown(Play::Input::MouseButton::BUTTON_LEFT))
	{
		this->fired = false;
	}
}

void Reticle::Draw()
{
	const int reticleHalfSize = 2; // half (size - 1)
	Play::DrawLine(this->GetPosition() + Play::Vector2D(-reticleHalfSize, 0), this->GetPosition() + Play::Vector2D(reticleHalfSize, 0), Play::cGreen);
	Play::DrawLine(this->GetPosition() + Play::Vector2D(0, reticleHalfSize), this->GetPosition() + Play::Vector2D(0, -reticleHalfSize), Play::cGreen);
}

MissileBase* Reticle::GetClosestMissileBase(Play::Point2D targetPosition) const
{
	/* //////////////////////////////////
	* DOD:
	* List of missible bases should be provided directly instead of checking every object
	* 
	* Also closes based could be by default first from bases list
	*/

	MissileBase* closestBase = nullptr;
	float closestDistance = 9999999999.0f;

	/* //////////////////////////////////
	* DOD:
	* Still not good enough
	* Change to more explicit implementation handled by manager
	* Maybe list of bases could be provided as parameter
	*/

	//std::vector<GameObject*> gameObjects = gameStateManager->GetGameObjects();
	auto bases = gameStateManager->GetGameObjectsOfType<MissileBase>();

	for (int i = 0; i < bases.size(); i++)
	{
		// Is missile base?
		MissileBase* base = dynamic_cast<MissileBase*>(bases[i]);

		// the object is a base, check for the closest
		float distance = (base->GetPosition() - this->GetPosition()).Length();
		if (distance < closestDistance)
		{
			closestDistance = distance;
			closestBase = base;
		}
	}

	return closestBase;
}