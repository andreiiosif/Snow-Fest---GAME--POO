#include "../include/TextureManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* renderer)
{
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	if (tmpSurface)
	{
		/* Daca imaginea a fost incarcata cu succes, o transform in textura */
		SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
		return tex;
	}
	else
	{
		/* Daca imaginea nu a fost incarcata, afisez un mesaj de eroare si opresc executia programului */
		std::cout << "\nEROARE FATALA: Imaginea nu poate fi incarcata!";
		exit(EXIT_FAILURE);
	}
}

void TextureManager::DestroyTexture(SDL_Texture* tex)
{
	SDL_DestroyTexture(tex);
}
