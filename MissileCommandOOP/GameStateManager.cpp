#include <cassert>
#include "GameStateManager.h"
#include "GameObject.h"
#include "City.h"
#include "MissileBase.h"
#include "Missile.h"
#include "Reticle.h"

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
	Play::DrawRect(Play::Point2D(0, 0), Play::Point2D(this->worldWidth, groundLevel), Play::cYellow, true);

	// Spawn missiles 
	this->timeSinceLastHostileMissile += elapsedTime;
	// First, spawn incoming hostile missiles if necessary
	if (this->timeSinceLastHostileMissile >= this->timeBetweenHostileMissiles)
	{
		for (size_t i = 0; i < 1; i++)
		{
			/* //////////////////////////////////
			* DOD:
			* Use constants??
			*/

			Play::Point2D origin = Play::Point2D(Play::RandomRoll(this->worldWidth), this->worldHeight);
			Play::Point2D target = Play::Point2D(Play::RandomRoll(this->worldWidth), this->groundLevel);
			Missile* missile = new Missile(origin, target, Play::cRed, this->missileSpeed);
			this->AddGameObject(missile);
		}
		this->timeSinceLastHostileMissile = 0;
		this->timeBetweenHostileMissiles = std::fmaxf(0.005f, this->timeBetweenHostileMissiles - 0.035f);
		this->missileSpeed += 0.5f;
	}

	// simulate all game objects
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) 
	{
		// Get group
		std::vector typeObjects = it->second;
		int size = typeObjects.size();

		// Simulate group
		for (int i = size - 1; i >= 0; i--)
		{
			// Delete
			if (typeObjects[i]->scheduledDelete)
			{
				delete it->second[i];
				it->second.erase(it->second.begin() + i);
				continue;
			}

			typeObjects[i]->Simulate(elapsedTime);

			// Draw
			typeObjects[i]->Draw();
		}
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
	std::type_index type = std::type_index(typeid(*gameObject));
	this->gameObjects[type].push_back(gameObject); // 
	gameObject->gameStateManager = this;
}

bool GameStateManager::RemoveGameObject(GameObject* gameObject)
{
	// Get objects of type
	std::type_index type = std::type_index(typeid(*gameObject));
	std::vector typeObjects = this->gameObjects[type];

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
	// Reticle
	Reticle* reticle = new Reticle();
	reticle->SetPosition(Play::Input::GetMousePos());
	this->AddGameObject(reticle);

	// Cities
	float offset = this->worldWidth / 7;

	for (size_t i = 0; i < 6; i++)
	{
		City* city = new City();
		city->SetPosition(Play::Point2D(float(i) * offset + offset, groundLevel));
		this->AddGameObject(city);
	}

	// Bases
	offset = ((float)this->worldWidth / 7.0f);

	for (size_t i = 0; i < 3; i++)
	{
		MissileBase* base = new MissileBase();
		base->SetPosition(Play::Point2D((offset * i * 2.0f) + offset * 1.4f, groundLevel));
		this->AddGameObject(base);
	}
}