#pragma once

#include "SDL_image.h"

#define EXIT_FAILURE 1

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);
	static void DestroyTexture(SDL_Texture* tex);
};