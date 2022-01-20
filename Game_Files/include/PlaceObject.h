#pragma once

#include "Entity.h"
#include "SDL_image.h"
#include "TextureManager.h"

class PlaceObject : public Entity
{
public:
	SDL_Texture* objectTex;
	SDL_Rect srcR;
	char* objectPath;

	PlaceObject() = default;
	PlaceObject(const char* objectPath, SDL_Renderer* renderer);
	~PlaceObject();
	
	void init(int x, int y, int w, int h);
	void draw();
};

