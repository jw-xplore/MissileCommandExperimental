#pragma once
#include <vector>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <string>

// Forward declarations
class GameObject;




// GameStateManager keeps track of the game state
class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void Update(float elapsedTime);
	
	//GameObject* GetFirstGameObject();
	//std::vector<GameObject*> GetGameObjects(); // Should be removed later

	template<class T>
	std::vector<GameObject*> GetGameObjectsOfType() const;

	// Return all objects that are exactly required class or inherits from the class
	template<class T>
	std::vector<GameObject*> GetGameObjectsOfRelatedType() const;

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

private:
	int worldWidth;
	int worldHeight;

	float timeSinceLastHostileMissile;
	float timeBetweenHostileMissiles;
	float missileSpeed;

	const float groundLevel = 16.0f;

	// Map of GameObject vectors defined by class type
	std::map<std::type_index, std::vector<GameObject*>> gameObjects;
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