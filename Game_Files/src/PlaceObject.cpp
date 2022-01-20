#include "../include/PlaceObject.h"
#include "../include/TextureManager.h"

PlaceObject::PlaceObject(const char* objectPath, SDL_Renderer* renderer) : Entity(renderer)
{
	if (objectPath)
	{
		/* Copiez sirul de caractere in campul clasei */
		this->objectPath = new char[strlen(objectPath) + 1];
		strcpy_s(this->objectPath, strlen(objectPath) + 1, objectPath);
		/* Incarc imaginea ca suprafata temporara */
		objectTex = TextureManager::LoadTexture(objectPath, renderer);
		//std::cout << "\nPlaceObject: PlaceObject(" << objectPath << ");";
	}
	else
	{
		/* Daca calea catre imagine nu este cea corecta, afisez un mesaj de eroare si opresc executia programului */
		std::cout << "\nEROARE FATALA: Imaginea nu a putut fi accesata!";
		exit(EXIT_FAILURE);
	}
}

PlaceObject::~PlaceObject()
{
	if (objectTex) TextureManager::DestroyTexture(objectTex);
	if (objectPath) delete[]objectPath;
}

void PlaceObject::init(int x, int y, int w, int h)
{
	srcR.x = x;
	srcR.y = y;
	srcR.w = w;
	srcR.h = h;
}

void PlaceObject::draw()
{
	SDL_RenderCopy(renderer, objectTex, NULL, &srcR);
}
