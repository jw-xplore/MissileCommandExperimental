#include <cassert>
#include "GameStateManager.h"
#include "GameObject.h"
#include "MissileBase.h"

GameStateManager::GameStateManager() : worldHeight(100), worldWidth(100)
{
	// reset game to initialized, but empty state.
	ClearGame();
}

GameStateManager::~GameStateManager()
{
	ClearGame();
}

void GameStateManager::Update(float elapsedTime)
{
	// Restart game
	if (Play::KeyDown(Play::KEY_ENTER))
	{
		this->ClearGame();
		this->NewGame();
	}

	// Ground draw
	Play::DrawRect(Play::Point2D(0, 0), Play::Point2D(this->worldWidth, GROUND_LEVEL), Play::cYellow, true);

	// Simulate
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
	{
		// Get group
		std::vector<GameObject*> typeObjects = it->second;
		int size = typeObjects.size();

		// Handle delete
		for (int i = size - 1; i >= 0; i--)
		{
			if (typeObjects[i]->scheduledDelete)
			{
				delete it->second[i];
				it->second.erase(it->second.begin() + i);
				continue;
			}
		}

		// Simulate call
		//this->simulateFncMap.at(it->first)(typeObjects, elapsedTime);
	}

	// Simulate and draw
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
	{
		std::vector<GameObject*> typeObjects = it->second;

		switch (it->first)
		{
		case EObjectType::RETICLE:
		{
			Reticle::simulate(typeObjects[0], this, elapsedTime);
			Reticle::draw(typeObjects);
			break;
		}

		case EObjectType::CITY:
		{
			SpriteDraw::drawSprite(typeObjects, spriteComponents);
			break;
		}

		case EObjectType::MISSILE_BASE:
		{
			SpriteDraw::drawSprite(typeObjects, spriteComponents);
			break;
		}

		}

		//this->simulateFncMap.at(it->first)(typeObjects, elapsedTime);
		//this->drawFncMap.at(it->first)(typeObjects);
	}
}

void GameStateManager::SetWorldSize(int width, int height)
{
	this->worldWidth = width;
	this->worldHeight = height;
}

// Add object to array with specific class type of GameObject
void GameStateManager::AddGameObject(GameObject* gameObject)
{
	// Setup type and id
	EObjectType type = gameObject->GetType();
	gameObject->SetId(idToAssign);
	idToAssign++;

	// Add in list
	this->m_GameObjects[type].push_back(gameObject);
	gameObject->gameStateManager = this;
}

bool GameStateManager::RemoveGameObject(GameObject* gameObject)
{
	// Get objects of type
	std::vector typeObjects = this->m_GameObjects[gameObject->GetType()];

	for (int i = typeObjects.size() - 1; i >= 0; i--)
	{
		// Remove object
		if (typeObjects[i] == gameObject)
		{
			typeObjects.erase(typeObjects.begin() + i);
			delete gameObject;
			return true;
		}
	}

	// Object not found
	return false;
}

void GameStateManager::ClearGame()
{
	// Clear all game objects
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		for (int i = it->second.size() - 1; i >= 0; i--)
		{
			delete it->second[i];
			it->second.erase(it->second.begin() + i);
		}
	}

	// Restart game setup
	this->timeSinceLastHostileMissile = 0;
	this->timeBetweenHostileMissiles = 3.0f;
	this->missileSpeed = 10.0f;
}

void GameStateManager::NewGame()
{
	/*
	// Reticle
	Reticle* reticle = new Reticle();
	reticle->SetPosition(Play::Input::GetMousePos());
	this->AddGameObject(reticle);

	// Cities
	float offset = this->worldWidth / 7;

	for (size_t i = 0; i < 6; i++)
	{
		City* city = new City();
		city->SetPosition(Play::Point2D(float(i) * offset + offset, GROUND_LEVEL));
		this->AddGameObject(city);
	}

	// Bases
	offset = ((float)this->worldWidth / 7.0f);

	for (size_t i = 0; i < 3; i++)
	{
		MissileBase* base = new MissileBase();
		base->SetPosition(Play::Point2D((offset * i * 2.0f) + offset * 1.4f, GROUND_LEVEL));
		this->AddGameObject(base);
	}
	*/

	// Reticle
	GameObject* reticle = new GameObject(EObjectType::RETICLE);
	this->AddGameObject(reticle);

	// Cities
	float offset = this->worldWidth / 7;

	for (size_t i = 0; i < 6; i++)
	{
		GameObject* city = new GameObject(EObjectType::CITY);
		city->SetPosition(Play::Point2D(float(i) * offset + offset, GROUND_LEVEL));
		this->AddGameObject(city);

		spriteComponents[city->GetId()] = SpriteConstants::SPR_CITY;
	}

	// Bases
	offset = ((float)this->worldWidth / 7.0f);

	for (size_t i = 0; i < 3; i++)
	{
		GameObject* base = new GameObject(EObjectType::MISSILE_BASE);
		base->SetPosition(Play::Point2D((offset * i * 2.0f) + offset * 1.4f, GROUND_LEVEL));
		this->AddGameObject(base);

		spriteComponents[base->GetId()] = SpriteConstants::SPR_MISSILE_BASE;
	}
}

std::vector<GameObject*> GameStateManager::GetGameObjectsOfType(EObjectType type)
{
	return m_GameObjects[type];
}

void GameStateManager::AddMissileBaseComponent(GameObject* gameObject)
{
	using namespace MissileBase;
	missileBaseComponents[gameObject->GetId()] = MissileBaseComponent();
}

std::map<int, MissileBase::MissileBaseComponent> GameStateManager::GetMissileBaseComponets()
{
	return missileBaseComponents;
}

// Missiles management

/*
void GameStateManager::UpdateMissiles(std::vector<Missile*> missiles, float elapsedTime)
{
	for (int i = 0; i < missiles.size(); i++)
	{
		missiles[i]->distanceTravelled += missiles[i]->speed * elapsedTime;
		Play::Point2D currentPosition = missiles[i]->origin + missiles[i]->GetTravellingDirection() * missiles[i]->distanceTravelled;
		missiles[i]->SetPosition(currentPosition);

		if (missiles[i]->distanceTravelled >= missiles[i]->GetDistanceFromOriginToTarget() || missiles[i]->IsDestroyed())
		{
			Explosion* explosion = new Explosion(missiles[i]->GetPosition());
			this->AddGameObject(explosion);

			// Destroy this object
			missiles[i]->ScheduleDelete();
		}
	}
}
*/

/*
void GameStateManager::SpawnMissile()
{
	// Create missile
	Play::Point2D origin = Play::Point2D(Play::RandomRoll(this->worldWidth), this->worldHeight);
	Play::Point2D target = Play::Point2D(Play::RandomRoll(this->worldWidth), this->groundLevel);
	Missile* missile = new Missile(origin, target, Play::cRed, this->missileSpeed);
	this->AddGameObject(missile);

	// Create transformation entry

	// Update game state
	this->timeSinceLastHostileMissile = 0;
	this->timeBetweenHostileMissiles = std::fmaxf(0.005f, this->timeBetweenHostileMissiles - 0.035f);
	this->missileSpeed += 0.5f;
}

*/