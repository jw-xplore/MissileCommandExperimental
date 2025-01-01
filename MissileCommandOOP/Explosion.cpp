#include "Explosion.h"
#include "GameStateManager.h"
#include "Destroyable.h"
#include <vector>

/*
Explosion::Explosion(Play::Point2D position) :
	hasExploded(false),
	maxRadius(16.0f),
	currentRadius(maxRadius / 2.0f),
	alternateColour(0)
{
	this->SetPosition(position);
}

*/

/* //////////////////////////////////
* DOD:
* Remove simulate as it will continously check when to explode and then it will just execute delete once
* Should be trigger from other object on collision
*/

/*
void Explosion::Simulate(float elapsedTime)
{
	if (!this->hasExploded)
	{
		Explode();
	}

	// simulate explosion for x seconds, then schedule for deletion.
	const float expansionSpeed = ((maxRadius / 2.0f)) * elapsedTime * 12.0f;
	currentRadius = std::fminf(this->currentRadius + expansionSpeed, maxRadius);
	if (currentRadius == maxRadius)
	{
		this->ScheduleDelete();
	}


}
*/


/* //////////////////////////////////
	* DOD:
	* Define this in constants?
	*/

/*
void Explosion::Draw()
{
	const Play::Colour colours[4] = {
		Play::cWhite,
		Play::cRed,
		Play::cBlue,
		Play::cYellow
	};

	this->alternateColour = (this->alternateColour + 1) % 8;
	int colourIndex = this->alternateColour / 2;

	Play::DrawCircle(this->position, this->currentRadius, colours[colourIndex]);
}
*/

/* //////////////////////////////////
	* DOD:
	* Still not good enough
	* Change to more explicit implementation handled by manager??
	*/

/*
void Explosion::Explode()
{
	Play::PlayAudio("Explode");


	// Get destroyables and setup variables
	auto destroyables = gameStateManager->GetGameObjectsOfRelatedType<Destroyable>();
	
	Destroyable* destroyable;
	Play::Point2D destroyablePos;
	float fastDist = this->maxRadius * 2;

	for (int i = 0; i < destroyables.size(); i++)
	{
		// Object check
		if (destroyables[i] == this)
			continue;

		destroyable = dynamic_cast<Destroyable*>(destroyables[i]);

		// Fast collision check
		destroyablePos = destroyable->GetPosition();

		if (abs(destroyablePos.x - this->GetPosition().x) > fastDist ||
			abs(destroyablePos.y - this->GetPosition().y) > fastDist)
			continue;

		// The object is destroyable, reduce health if within max radius
		if ((destroyablePos - this->GetPosition()).Length() < this->maxRadius)
		{
			destroyable->ReduceHealth(50);
		}
	}


	this->hasExploded = true;
}
*/