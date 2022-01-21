#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "PlaceObject.h"
#include "Player.h"

class Map
{
private:
	SDL_Texture* mapTex;
	SDL_Renderer* renderer;
	char* mapPath;
	uint8_t map[12][16];
	PlaceObject** objects;
	uint32_t objects_size;
public:
	Map() = default;
	Map(const char* mapPath, SDL_Renderer* renderer, uint8_t level);
	~Map();

	void loadMap(uint8_t matrix[12][16]);
	void updateMap();
	void draw();

	void Collision(Player *player, char dir);
	bool GetPoints(Player* player);
	bool GetFinish(Player* player);
	bool onGround(Player* player);
	bool GetOut(Player* player);
};
