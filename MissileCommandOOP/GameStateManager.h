#pragma once
#include <vector>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <string>

#include "Missile.h"
#include "Constants.h"
#include "Reticle.h"
#include "SpriteDraw.h"
#include "MissileBase.h"
#include "Explosion.h"

// Forward declarations
class GameObject;

// GameStateManager keeps track of the game state
class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void Update(float elapsedTime);

	void SetWorldSize(int width, int height);

	// Add a game object to the game state. This makes the game object active and automatically updated.
	//void AddGameObject(GameObject* gameObject);

	void AddGameObject(GameObject* gameObject);

	// Removes a game object from the list of active objects. This deletes the object, and returns true or false if it was successful or not.
	bool RemoveGameObject(GameObject* gameObject);

	// Starts a new game by instantiating all necessary objects.
	void NewGame();
	// Destorys all game objects and wipes the game clean.
	void ClearGame();

	//void UpdateMissiles(std::vector<Missile*> missiles, float elapsedTime);

	//void SpawnMissile();

	std::vector<GameObject*> GetGameObjectsOfType(EObjectType type);

	// Components
	void AddMissileBaseComponent(GameObject* gameObject);
	std::map<int, MissileBase::MissileBaseComponent> GetMissileBaseComponets();

	Missile::MissileComponent* AddMissileComponent(GameObject* gameObject);

	//Explosion::ExplosionComponent* AddExplosionComponent(GameObject* gameObject);

private:
	int idToAssign = 0;

	int worldWidth;
	int worldHeight;

	float timeSinceLastHostileMissile;
	float timeBetweenHostileMissiles;
	float missileSpeed;

	// Map of GameObject vectors defined by class type
	std::map<std::type_index, std::vector<GameObject*>> gameObjects;

	std::map<EObjectType, std::vector<GameObject*>> m_GameObjects;
	std::vector<GameObject*>* missiles;
	//std::vector<GameObject*>* missiles;

	// Components
	std::map<int, const char*> spriteComponents;
	std::map<int, MissileBase::MissileBaseComponent> missileBaseComponents;
	std::map<int, Missile::MissileComponent> missileComponents;
	std::map<int, int> healthComponents;
	std::map<int, Explosion::ExplosionComponent> explosionComponent;
	//std::map<int, Explosion::ExplosionComponent> explosionComponents;
	//std::map<int, Expl::ExplosionTest> explTestMap;
};
