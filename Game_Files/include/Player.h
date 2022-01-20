#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Entity.h"

#define pas 4
#define gravitatie 30

class Player : public Entity
{
private:
	SDL_Texture* playerTex;
	SDL_Texture* Green_Dev;
	SDL_Rect srcR, destR;
	char direction, state, jumpDir;
	char* playerPath;
	int gravity;
	Vec2D velocity;
public:
	Player() = default;
	Player(const char *playerPath, SDL_Renderer* renderer);
	~Player();

	SDL_Rect getSource();
	SDL_Rect getDestination();
	int getGravity();
	char getDirection();
	char getJumpState();

	void init(int x, int y);
	void update_velocity(Vec2D P);
	void update_position();
	void draw();

	void setState(char C);
	void setGravity(int gravity);
	void setJumpState(char C);
	void fall();

	void update_green();
};



