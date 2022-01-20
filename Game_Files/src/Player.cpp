#include "../include/Player.h"

Player::Player(const char *playerPath, SDL_Renderer* renderer) : Entity(renderer)
{
	if (playerPath)
	{
		/* Copiez sirul de caractere in campul clasei */
		this->playerPath = new char[strlen(playerPath) + 1];
		strcpy_s(this->playerPath, strlen(playerPath) + 1, playerPath);
		
		/* Incarc imaginea ca suprafata temporara */
		playerTex = TextureManager::LoadTexture(playerPath, renderer);
		direction = 'R';
		
		/* Debugging tools */
		Green_Dev = TextureManager::LoadTexture("data/dev/greensc.png", renderer);
	}
	else 
	{
		/* Daca calea catre imagine nu este cea corecta, afisez un mesaj de eroare si opresc executia programului */
		std::cout << "\nEROARE FATALA: Imaginea nu a putut fi accesata!";
		exit(EXIT_FAILURE);
	}
}

Player::~Player()
{
	if (this->playerTex) TextureManager::DestroyTexture(this->playerTex);
	if (this->Green_Dev) TextureManager::DestroyTexture(this->Green_Dev);
	if (this->playerPath) delete[]playerPath;

	this->playerTex = nullptr;
	this->Green_Dev = nullptr;
	this->playerPath = nullptr;
}

SDL_Rect Player::getSource()
{
	return this->srcR;
}

SDL_Rect Player::getDestination()
{
	return this->destR;
}

int Player::getGravity()
{
	return gravity;
}

char Player::getDirection()
{
	return direction;
}

char Player::getJumpState()
{
	return this->jumpDir;
}

void Player::init(int x, int y)
{
	srcR.x = x;
	srcR.y = y;
	srcR.w = srcR.h = 50;
	destR.x = x;
	destR.y = y;
	destR.w = destR.h = 50;
}

void Player::update_velocity(Vec2D P)
{
	velocity = P;
}

void Player::update_position()
{
	if (state == 'X')
	{
		destR.x += velocity.x;
		destR.y += velocity.y;
		srcR = destR;

		if (velocity.x < 0 && direction == 'R')
		{
			direction = 'L';
			//std::cout << "\nINFO: Schimba directie la stanga!";

			playerPath[strlen(playerPath) - 5] = 'L';
			TextureManager::DestroyTexture(playerTex);
			playerTex = TextureManager::LoadTexture("data/png/Object/SnowManL.png", renderer);
		}
		else if (velocity.x > 0 && direction == 'L')
		{
			direction = 'R';
			//std::cout << "\nINFO: Schimba directie la dreapta!";

			playerPath[strlen(playerPath) - 5] = 'R';
			TextureManager::DestroyTexture(playerTex);
			playerTex = TextureManager::LoadTexture("data/png/Object/SnowManR.png", renderer);
		}

		this->setState(' ');
		velocity = { 0, 0 };
	}
	else
	{
		destR.y += gravity;
		srcR = destR;
	}
}

void Player::draw()
{
	//std::cout << "\nINFO: Pozitie noua " << destR.x << " " << destR.y << "\n";
	SDL_RenderCopy(renderer, playerTex, NULL, &destR);
	//update_green();
}

void Player::setState(char C)
{
	state = C;
}

void Player::setGravity(int gravity)
{
	this->gravity = gravity;
}

void Player::setJumpState(char C)
{
	this->jumpDir = C;
}

void Player::fall()
{
	this->gravity++;
}

void Player::update_green()
{
	//std::cout << "\nPlayer Info: Actualizare GREEN SCREEN!";
	int squareX = destR.x;
	int squareY = destR.y;
	
	SDL_Rect Rect; Rect.h = Rect.w = 50;
	/* Left */
	Rect.x = squareX - 50;
	Rect.y = squareY;
	SDL_RenderCopy(renderer, Green_Dev, NULL, &Rect);

	/* Up-Left */
	Rect.x = squareX - 50;
	Rect.y = squareY - 50;
	SDL_RenderCopy(renderer, Green_Dev, NULL, &Rect);

	/* Up */
	Rect.x = squareX;
	Rect.y = squareY - 50;
	SDL_RenderCopy(renderer, Green_Dev, NULL, &Rect);

	/* Up-Right */
	Rect.x = squareX + 50;
	Rect.y = squareY - 50;
	SDL_RenderCopy(renderer, Green_Dev, NULL, &Rect);

	/* Right */
	Rect.x = squareX + 50;
	Rect.y = squareY;
	SDL_RenderCopy(renderer, Green_Dev, NULL, &Rect);

	/* Down-Right */
	Rect.x = squareX + 50;
	Rect.y = squareY + 50;
	SDL_RenderCopy(renderer, Green_Dev, NULL, &Rect);

	/* Down */
	Rect.x = squareX;
	Rect.y = squareY + 50;
	SDL_RenderCopy(renderer, Green_Dev, NULL, &Rect);

	/* Down-Left */
	Rect.x = squareX - 50;
	Rect.y = squareY + 50;
	SDL_RenderCopy(renderer, Green_Dev, NULL, &Rect);
}
