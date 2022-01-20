#include <iostream>
#include <algorithm>

#include "../include/Map.h"

/*
	1-18 - Tiles
	19 - Crystal.png
	20 - IceBox.png
	21 - Stone.png
	22 - Tree_2.png
	23 - Sign_2.png
	24 - Igloo1.png
	25 - Igloo2.png
	26 - Coin.png
*/

Map::Map(const char* mapPath, SDL_Renderer* renderer, uint8_t level) : renderer(renderer)
{
	if (mapPath)
	{
		/* Copiez sirul de caractere in campul clasei */
		this->mapPath = new char[strlen(mapPath) + 1];
		strcpy_s(this->mapPath, strlen(mapPath) + 1, mapPath);

		/* Incarc imaginea ca suprafata temporara */
		mapTex = TextureManager::LoadTexture(mapPath, renderer);
		/* Creez obiectele ce trebuie amplasate pe harta*/
		this->objects = nullptr;
		uint8_t lvl[12][16] = { 0 };
		Utilities::Load_Levels(lvl, level);
		loadMap(lvl);

		std::cout << "\nMAP DATA: Map(" << mapPath << ");";
	}
	else
	{
		/* Daca calea catre imagine nu este cea corecta, afisez un mesaj de eroare si opresc executia programului */
		std::cout << "\nEROARE FATALA: Imaginea nu a putut fi accesata!";
		exit(EXIT_FAILURE);
	}
}

Map::~Map()
{
	if(this->mapTex) TextureManager::DestroyTexture(this->mapTex);
	if (mapPath) delete[]mapPath;
	for (uint32_t i = 0; i < objects_size; i++)
	{
		if (objects[i]) delete objects[i];
	}
	if (objects) delete[] objects;

	this->mapTex = nullptr;
	this->mapPath = nullptr;
	this->objects = nullptr;
}

void Map::loadMap(uint8_t matrix[12][16])
{
	for (uint16_t i = 0; i < 12; i++)
	{
		for (uint16_t j = 0; j < 16; j++)
		{
			map[i][j] = matrix[i][j];
		}
	}
	updateMap();
}

void Map::updateMap()
{
	objects_size = 0;
	for (uint16_t i = 0; i < 12; i++)
	{
		for (uint16_t j = 0; j < 16; j++)
		{
			if (map[i][j]) objects_size++;
		}
	}
	if (objects)
	{
		for (uint16_t ob = 0; ob < objects_size; ob++)
		{
			if (objects[ob]) delete objects[ob];
		}
	}
	if (objects) delete[]objects;
	objects = new PlaceObject * [objects_size];

	uint16_t objects_idx = 0;

	for (uint16_t i = 0; i < 12; i++)
	{
		for (uint16_t j = 0; j < 16; j++)
		{
			switch (map[i][j])
			{
			case 1:
				objects[objects_idx] = new PlaceObject("data/png/Tiles/1.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 14 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 2:
				objects[objects_idx] = new PlaceObject("data/png/Tiles/2.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 14 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 3:
				objects[objects_idx] = new PlaceObject("data/png/Tiles/3.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 14 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 4:
				objects[objects_idx] = new PlaceObject("data/png/Tiles/4.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 14 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 5:
				objects[objects_idx] = new PlaceObject("data/png/Tiles/5.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 14 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 6:
				objects[objects_idx] = new PlaceObject("data/png/Tiles/6.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 14 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 9:
				objects[objects_idx] = new PlaceObject("data/png/Tiles/9.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 14 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 12:
				objects[objects_idx] = new PlaceObject("data/png/Tiles/12.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 14 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 13:
				objects[objects_idx] = new PlaceObject("data/png/Tiles/13.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 14 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 14:
				objects[objects_idx] = new PlaceObject("data/png/Tiles/14.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 14 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 15:
				objects[objects_idx] = new PlaceObject("data/png/Tiles/15.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 15 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 16:
				objects[objects_idx] = new PlaceObject("data/png/Tiles/16.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 16 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 19:
				objects[objects_idx] = new PlaceObject("data/png/Object/Crystal.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 16 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 20:
				objects[objects_idx] = new PlaceObject("data/png/Object/IceBox.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 16 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 21:
				objects[objects_idx] = new PlaceObject("data/png/Object/Stone.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 16 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 22:
				objects[objects_idx] = new PlaceObject("data/png/Object/Tree_2.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 16 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 23:
				objects[objects_idx] = new PlaceObject("data/png/Object/Sign_2.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 16 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 24:
				objects[objects_idx] = new PlaceObject("data/png/Object/Igloo1.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 16 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 25:
				objects[objects_idx] = new PlaceObject("data/png/Object/Igloo2.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 16 la pozitia " << j * 50 << " " << i * 50;
				break;
			case 26:
				objects[objects_idx] = new PlaceObject("data/png/Object/Coin.png", renderer);
				objects[objects_idx++]->init(j * 50, i * 50, 50, 50);
				//std::cout << "\n\tAmplasez obiect tip 16 la pozitia " << j * 50 << " " << i * 50;
				break;
			default:
				break;
			}
		}
	}
}

void Map::draw()
{
	SDL_RenderCopy(renderer, mapTex, NULL, NULL);
	for (uint16_t i = 0; i < objects_size; i++)
	{
		SDL_RenderCopy(renderer, objects[i]->objectTex, NULL, &objects[i]->srcR);
	}
}

void Map::Collision(Player *player, char dir)
{
	SDL_Rect srcR = player->getSource();
	player->setState('X');

	Vec2D velocity = { 0, 0 };

	if (onGround(player)) player->setGravity(0);

	int distance = 0, xr = 0, yr = 0;

	if (dir == 'A')
	{
		distance = pas;
		xr = -1;
		yr = 0;
	}
	else if (dir == 'D')
	{
		distance = pas;
		xr = 1;
		yr = 0;
	}
	else if (dir == 'W')
	{
		player->setGravity(-gravitatie);
		player->setJumpState('N');

		distance = gravitatie;
		xr = 0;
		yr = -1;
	}
	else if (dir == 'Q')
	{
		player->setGravity(-gravitatie);
		player->setJumpState('L');

		distance = gravitatie / 2 + 1;
		xr = -1;
		yr = -1;
	}
	else if (dir == 'E')
	{
		player->setGravity(-gravitatie);
		player->setJumpState('R');

		distance = gravitatie / 2 + 1;
		xr = 1;
		yr = -1;
	}
	else if (dir == 'S' && player->getGravity())
	{
		xr = 0;
		if (player->getGravity() < 0)
		{
			//std::cout << "\n" << player->getGravity();
			if (player->getJumpState() == 'L') xr = -1;
			else if(player->getJumpState() == 'R') xr = 1;
		}
		if (player->getGravity() < 0)
		{
			distance = -player->getGravity() / 2 + 1;
			yr = -1;
		}
		else if (player->getGravity() > 0)
		{
			distance = player->getGravity() / 2 + 2;
			yr = 1;
		}
	}
	int bestX = srcR.x, bestY = srcR.y;
	//std::cout << "\nIncepe simularea";
	for (int k = 1; k <= distance; k++)
	{
		int auxX, auxY;

		if (player->getJumpState() != 'N' && (dir == 'S' || dir == 'Q' || dir == 'E')) auxX = srcR.x + xr * (k / 2);
		else auxX = srcR.x + xr * k;
		
		auxY = srcR.y + yr * k;
		//std::cout << "\nPozitie de testare " << auxY << " " << auxX;
		bool colission = false;
		for (uint16_t i = 0; i < 12 && !colission; i++)
		{
			for (uint16_t j = 0; j < 16 && !colission; j++)
			{
				if (map[i][j] >= 1 && map[i][j] <= 22)
				{
					//std::cout << "\n\nPozitia curenta: " << "[ " << auxY << "," << auxX << "]";
					//std::cout << "\nPosibile coliziuni: " << "[ " << i * 50 << "," << j * 50 << "]";
					if (Utilities::rectangles_overlap({ auxY, auxX + 50 }, { i * 50, j * 50 + 50 }, srcR.h) || Utilities::outOfGame(auxX, auxY))
					{
						//std::cout << "\nColiziune" << i * 50 - auxY << '\n';
						colission = true;
					}
				}
			}
		}
		if (!colission)
		{
			bestX = auxX;
			bestY = auxY;
		}
		else break;
	}
	velocity = { bestX - srcR.x, bestY - srcR.y };

	//std::cout << "Poz curent " << srcR.y << " " << srcR.x << " si viitor " << bestY << " " << bestX << '\n';

	player->update_velocity(velocity);
	if (dir != 'A' && dir != 'D' && !onGround(player))
	{
		player->fall();
	}
}

bool Map::GetPoints(Player* player)
{
	SDL_Rect srcR = player->getSource();
	int auxX = srcR.x;
	int auxY = srcR.y;
	//std::cout << "\nPozitie de testare " << auxY << " " << auxX;
	bool colission = false;
	uint16_t i = auxY / 50;
	for (uint16_t j = 0; j < 16 && !colission; j++)
	{
		if (map[i][j] == 26)
		{
			//std::cout << "\n\nPozitia curenta: " << "[ " << auxY << "," << auxX << "]";
			//std::cout << "\nPosibile coliziuni: " << "[ " << i * 50 << "," << j * 50 << "]";
			if (Utilities::rectangles_overlap({ auxY, auxX + 50 }, { i * 50, j * 50 + 50 }, srcR.h) || Utilities::outOfGame(auxX, auxY))
			{
				//std::cout << "\nColiziune" << i * 50 - auxY << '\n';
				colission = true;
				map[i][j] = 0;
				PlaySound(TEXT("data/sound/get_coin.wav"), NULL, SND_ASYNC);
			}
		}
	}
	if (colission) updateMap();
	return colission;
}

bool Map::GetFinish(Player* player)
{
	SDL_Rect srcR = player->getSource();
	int auxX = srcR.x;
	int auxY = srcR.y;
	//std::cout << "\nPozitie de testare " << auxY << " " << auxX;
	bool colission = false;
	uint16_t i = auxY / 50;
	for (uint16_t j = 0; j < 16 && !colission; j++)
	{
		if (map[i][j] == 25)
		{
			//std::cout << "\n\nPozitia curenta: " << "[ " << auxY << "," << auxX << "]";
			//std::cout << "\nPosibile coliziuni: " << "[ " << i * 50 << "," << j * 50 << "]";
			if (Utilities::rectangles_overlap({ auxY, auxX + 50 }, { i * 50, j * 50 + 50 }, srcR.h) || Utilities::outOfGame(auxX, auxY))
			{
				//std::cout << "\nColiziune" << i * 50 - auxY << '\n';
				colission = true;
				map[i][j] = 0;
				PlaySound(TEXT("data/sound/final.wav"), NULL, SND_ASYNC);
			}
		}
	}
	if (colission) updateMap();
	return colission;
}

bool Map::onGround(Player *player)
{
	SDL_Rect srcR = player->getSource();
	int auxX = srcR.x;
	int auxY = srcR.y + 1;
	//std::cout << "\nPozitie de testare " << auxY << " " << auxX;
	bool colission = false;
	for (uint16_t i = 0; i < 12 && !colission; i++)
	{
		for (uint16_t j = 0; j < 16 && !colission; j++)
		{
			if (map[i][j] >= 1 && map[i][j] <= 22)
			{
				//std::cout << "\n\nPozitia curenta: " << "[ " << auxY << "," << auxX << "]";
				//std::cout << "\nPosibile coliziuni: " << "[ " << i * 50 << "," << j * 50 << "]";
				if (Utilities::rectangles_overlap({ auxY, auxX + 50 }, { i * 50, j * 50 + 50 }, srcR.h) || Utilities::outOfGame(auxX, auxY))
				{
					//std::cout << "\nColiziune" << i * 50 - auxY << '\n';
					colission = true;
				}
			}
		}
	}
	return colission;
}

