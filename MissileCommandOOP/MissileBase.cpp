#include "MissileBase.h"
#include "Missile.h"
#include "GameStateManager.h"

void MissileBase::simulate(vector<GameObject*> bases, map<int, MissileBaseComponent> componets, float elapsedTime)
{
	for (int i = 0; i < bases.size(); i++)
	{
		MissileBaseComponent baseCmp = componets[bases[i]->GetId()];

		if (baseCmp.missileCount < baseCmp.maxMissiles)
		{
			// Progress reload time
			baseCmp.timeSinceReload += elapsedTime;

			// Reload
			if (baseCmp.timeSinceReload > baseCmp.reloadTime)
			{
				baseCmp.missileCount++;
				baseCmp.timeSinceReload = 0;
			}
		}
	}
}

void MissileBase::fireMissile(GameObject* base, MissileBaseComponent* component, GameStateManager* manager, Point2D target)
{
	//if (this->IsDestroyed())
		//return;

	if (component->missileCount > 0)
	{
		GameObject* missile = new GameObject(EObjectType::MISSILE);


		//(this->GetPosition(), target, Play::cBlue, this->missileSpeed);
		// 
		
		// Register in manager
		//manager->AddGameObject(missile);
		//manager->AddMissileBaseComponent(base);
		//base->gameStateManager->AddGameObject(missile, EObjectType::MISSILE);


		component->missileCount--;
		Play::PlayAudio("Fire");
	}
}

/*
MissileBase::MissileBase() :
	maxMissiles(10),
	missileCount(maxMissiles),
	timeSinceReload(0),
	reloadTime(1),
	missileSpeed(50.0f)
{
	this->SetStructureSprite("missile_base");
}

void MissileBase::Draw()
{
	Structure::Draw();

	if (this->IsDestroyed())
		return;

	std::string countText = std::to_string(this->missileCount);
	Play::DrawDebugText(this->GetPosition() + Play::Vector2f(6, -8), countText.c_str(), Play::cBlack);
}

void MissileBase::Simulate(float elapsedTime)
{
	if (missileCount < maxMissiles)
	{
		timeSinceReload += elapsedTime;
		if (timeSinceReload > reloadTime)
		{
			missileCount++;
			timeSinceReload = 0;
		}
	}
}

void MissileBase::FireMissile(Play::Point2D target)
{
	if (this->IsDestroyed())
		return;

	if (this->missileCount > 0)
	{
		Missile* missile = new Missile(this->GetPosition(), target, Play::cBlue, this->missileSpeed);
		this->gameStateManager->AddGameObject(missile, EObjectType::MISSILE);
		this->missileCount--;
		Play::PlayAudio("Fire");
	}
}
*/