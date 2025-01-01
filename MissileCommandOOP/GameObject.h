#pragma once
#include "Play.h"
#include "Constants.h"

class GameStateManager;

// All game object types inherit from game object base class
class GameObject
{
public:
	GameObject(EObjectType type);
	~GameObject();

	Play::Point2D GetPosition() const;

	void SetPosition(Play::Point2D const& newPosition);

	// call to schedule the object for deletion.
	void ScheduleDelete();

	EObjectType GetType();

	friend class GameStateManager;

protected:
	friend class GameStateManager;

	// This is executed by the game state manager once per frame. Override in subclass.
	//virtual void Simulate(float elapsedTime);

	// This is executed by the game state manager once per frame, after simulate. Override in subclass.
	// pure virtual makes this class an abstract class!
	//virtual void Draw() = 0; 

	/* //////////////////////////////////
	* DOD:
	* Positions handling could be handled in game state manager under single vector
	* Likely driven by some velocity value also grouped in the vector
	*/

	Play::Point2D position;

	// set to true if the object should be deleted by the game state manager when time is right
	bool scheduledDelete;

	EObjectType type;

	// All active game objects are in a linked list structure, managed by the game object manager.
	//GameObject* nextActiveGameObject;
	// This will be set to the game state manager when the object is attached to it.
	GameStateManager* gameStateManager;
};