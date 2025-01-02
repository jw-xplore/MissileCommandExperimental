#pragma once
#include "Play.h"

// Screen
const int DISPLAY_WIDTH = 240;
const int DISPLAY_HEIGHT = 160;
const int DISPLAY_SCALE = 4;

// Level
const float GROUND_LEVEL = 16.0f;

// Object types
enum EObjectType
{
	MISSILE,
	MISSILE_BASE,
	EXPLOSION,
	CITY,
	RETICLE,
};

// Colors
const Play::Colour EXPLOSION_COLORS[4] = {
		Play::cWhite,
		Play::cRed,
		Play::cBlue,
		Play::cYellow
};

// Sprites 
namespace SpriteConstants
{
	const char* const SPR_MISSILE_BASE = "missile_base";
	const char* const SPR_CITY = "city";
}