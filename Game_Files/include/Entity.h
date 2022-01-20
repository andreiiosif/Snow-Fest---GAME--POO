#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "Utilities.h"

class Entity
{
protected:
	SDL_Renderer* renderer;
protected:
	Entity(SDL_Renderer* renderer);
	virtual void draw() = 0;
};

