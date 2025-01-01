#pragma once
#include <vector>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <string>

#include "Missile.h"
#include "Constants.h"
#include "Reticle.h"

// Forward declarations
class GameObject;

// GameStateManager keeps track of the game state
class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void Update(float elapsedTime);
	
	template<class T>
	std::vector<GameObject*> GetGameObjectsOfType() const;

	// Return all objects that are exactly required class or inherits from the class
	template<class T>
	std::vector<GameObject*> GetGameObjectsOfRelatedType() const;

	void SetWorldSize(int width, int height);

	// Add a game object to the game state. This makes the game object active and automatically updated.
	//void AddGameObject(GameObject* gameObject);

	void AddGameObject(GameObject* gameObject, EObjectType type);

	// Removes a game object from the list of active objects. This deletes the object, and returns true or false if it was successful or not.
	bool RemoveGameObject(GameObject* gameObject);

	// Starts a new game by instantiating all necessary objects.
	void NewGame();
	// Destorys all game objects and wipes the game clean.
	void ClearGame();

	//void UpdateMissiles(std::vector<Missile*> missiles, float elapsedTime);

	//void SpawnMissile();

private:
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


	// Functions matching
	//void (*simulate_ptr) (std::vector<GameObject> gameObjects, float elapsedTime);

	// Update 
	using SimulateFnc = void(*)(std::vector<GameObject*> gameObjects, float elapsedTime);

	const std::map<EObjectType, SimulateFnc> simulateFncMap = {
		{ EObjectType::RETICLE, &Reticle::simulate },
	};

	// Draw
	using DrawFnc = void(*)(std::vector<GameObject*> gameObjects);

	const std::map<EObjectType, DrawFnc> drawFncMap = {
		{ EObjectType::RETICLE, &Reticle::draw },
	};
};


// Return all objects that are exactly of required class
template<class T>
std::vector<GameObject*> GameStateManager::GetGameObjectsOfType() const
{
	std::type_index type = std::type_index(typeid(T));
	auto iterator = gameObjects.find(std::type_index(typeid(T)));

	// Return empty vector if type is not found
	if (iterator == gameObjects.end())
		return {};

	return iterator->second;
}

// Return all objects that are of required class or inherits from the class
template<class T>
std::vector<GameObject*> GameStateManager::GetGameObjectsOfRelatedType() const
{
	std::vector<GameObject*> objects;
	//std::type_index type = std::type_index(typeid(T));

	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		// Skip empty list
		if (it->second.empty())
			continue;

		// Check object is related type
		if (dynamic_cast<T*>(it->second[0]) == nullptr)
			continue;

		// Add to related objects
		objects.insert(objects.begin(), it->second.begin(), it->second.end());
	}

	return objects;
}