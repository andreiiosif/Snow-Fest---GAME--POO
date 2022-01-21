#include "../include/Game.h"

Player* player;
Map* map;
PlaceObject* score;
PlaceObject* points;
PlaceObject* HomeScreen;

PlaceObject** totalTime;
PlaceObject** totalScore;
PlaceObject** bestScore;
uint32_t totalTime_digits;
uint32_t totalScore_digits;
uint32_t bestScore_digits;

Game::Game()
{
	std::cout << "\n\tGAME INFO: Game();";
}

Game::~Game()
{
	std::cout << "\n\t GAME INFO: ~Game();";
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "\n\tINFO: Subsystems Initialized!...\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "\n\tINFO: Window was created...\n";
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "\n\tINFO: Renderer was created...\n";
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	Utilities::Load_Game_Data(game_data);

	HomeScreen = new PlaceObject("data/png/BG/BG_main.png", renderer);
	HomeScreen->init(0, 0, 800, 600);

	PlaySound(TEXT("data/sound/winter_time.wav"), NULL, SND_LOOP | SND_ASYNC);
}

void Game::changeState(int old_state, int new_state)
{
	if (old_state == 0 || old_state == 3 || old_state == 4 || old_state == 5)
	{
		if (HomeScreen) delete HomeScreen;
		HomeScreen = nullptr;
	}
	else if (old_state == 1)
	{
		if (player) delete player;
		if (map) delete map;
		if (score) delete score;
		if (points) delete points;

		player = nullptr;
		map = nullptr;
		score = nullptr;
		points = nullptr;

		/* Salvez noile date */
		game_data.played_time += (SDL_GetTicks() - timestamp) / 1000;
		game_data.best_score = Max(game_data.best_score, cnt);
		game_data.total_score += cnt;

		Utilities::Save_Game_Data(game_data);
	}
	else if (old_state == 2)
	{
		if (HomeScreen) delete HomeScreen;

		for (uint32_t i = 0; i < totalTime_digits; i++)
		{
			if (totalTime[i]) delete totalTime[i];
		}
		if (totalTime) delete[]totalTime;

		for (uint32_t i = 0; i < bestScore_digits; i++)
		{
			if (bestScore[i]) delete bestScore[i];
		}
		if (bestScore) delete[]bestScore;

		for (uint32_t i = 0; i < totalScore_digits; i++)
		{
			if (totalScore[i]) delete totalScore[i];
		}
		if (totalScore) delete[]totalScore;

		HomeScreen = nullptr;
		totalTime = nullptr;
		bestScore = nullptr;
		totalScore = nullptr;
	}

	if (new_state == 0)
	{
		PlaySound(TEXT("data/sound/winter_time.wav"), NULL, SND_LOOP | SND_ASYNC);

		HomeScreen = new PlaceObject("data/png/BG/BG_main.png", renderer);
		HomeScreen->init(0, 0, 800, 600);
	}
	else if (new_state == 1)
	{
		PlaySound(TEXT("data/sound/enter_level.wav"), NULL, SND_ASYNC);
		cnt = 0;
		timestamp = SDL_GetTicks();
		if (game_data.level == 0) game_data.level++;

		player = new Player("data/png/Object/SnowManR.png", renderer);
		player->init(0, 100);

		map = new Map("data/png/BG/BG.png", renderer, game_data.level);

		score = new PlaceObject("data/png/BG/Score.png", renderer);
		score->init(0, 0, 100, 50);

		points = new PlaceObject("data/png/BG/Numbers/0.png", renderer);
		points->init(100, 0, 50, 50);
	}
	else if (new_state == 2)
	{
		/* Incarc datele */
		Utilities::Load_Game_Data(game_data);

		HomeScreen = new PlaceObject("data/png/BG/BG_stats.png", renderer);
		HomeScreen->init(0, 0, 800, 600);

		/* Convertire numere in texturi */
		uint32_t aux;
		char* s = nullptr;

		aux = game_data.played_time;
		totalTime_digits = Utilities::getDigits(game_data.played_time);
		totalTime = new PlaceObject * [totalTime_digits];
		for (uint32_t i = 0; i < totalTime_digits; i++)
		{
			s = Utilities::getSource(aux % 10);
			totalTime[i] = new PlaceObject(s, renderer);
			totalTime[i]->init(420 - i* 50, 275, 50, 50);
			aux /= 10;
		}

		aux = game_data.best_score;
		bestScore_digits = Utilities::getDigits(game_data.best_score);
		bestScore = new PlaceObject * [bestScore_digits];
		for (uint32_t i = 0; i < bestScore_digits; i++)
		{
			s = Utilities::getSource(aux % 10);
			bestScore[i] = new PlaceObject(s, renderer);
			bestScore[i]->init(370 - i * 50, 370, 50, 50);
			aux /= 10;
		}

		aux = game_data.total_score;
		totalScore_digits = Utilities::getDigits(game_data.total_score);
		totalScore = new PlaceObject * [totalScore_digits];
		for (uint32_t i = 0; i < totalScore_digits; i++)
		{
			s = Utilities::getSource(aux % 10);
			totalScore[i] = new PlaceObject(s, renderer);
			totalScore[i]->init(395 - i * 50, 450, 50, 50);
			aux /= 10;
		}
		
	}
	else if (new_state == 3)
	{
		HomeScreen = new PlaceObject("data/png/BG/BG_help.png", renderer);
		HomeScreen->init(0, 0, 800, 600);
	}
	else if (new_state == 4)
	{
		PlaySound(TEXT("data/sound/final.wav"), NULL, SND_ASYNC);
		HomeScreen = new PlaceObject("data/png/BG/BG_end.png", renderer);
		HomeScreen->init(0, 0, 800, 600);
	}
	else if (new_state == 5)
	{
		PlaySound(TEXT("data/sound/lost.wav"), NULL, SND_ASYNC);
		HomeScreen = new PlaceObject("data/png/BG/BG_lost.png", renderer);
		HomeScreen->init(0, 0, 800, 600);
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
	if (stare == 0)
	{
		SDL_MouseButtonEvent mouse = event.button;
		if (mouse.type == SDL_MOUSEBUTTONUP)
		{
			if (mouse.x >= 288 && mouse.x <= 288 + 187 && mouse.y >= 245 && mouse.y <= 245 + 89)
			{
				changeState(stare, 1);
				stare = 1;
			}
			else if (mouse.x >= 316 && mouse.x <= 316 + 169 && mouse.y >= 340 && mouse.y <= 340 + 86)
			{
				changeState(stare, 2);
				stare = 2;
			}
			else if(mouse.x >= 291 && mouse.x <= 291 + 161 && mouse.y >= 427 && mouse.y <= 427 + 85)
			{
				changeState(stare, 3);
				stare = 3;
			}
			else if(mouse.x >= 726 && mouse.x <= 726 + 66 && mouse.y >= 562 && mouse.y <= 562 + 30)
			{
				isRunning = false;
			}
		}
	}
	else if (stare == 1)
	{
		if (state[SDL_SCANCODE_ESCAPE])
		{
			changeState(stare, 0);
			stare = 0;
		}
		else if (map->onGround(player))
		{
			if (state[SDL_SCANCODE_Q])
			{
				map->Collision(player, 'Q');
				this->setActKey(true);
			}
			else if (state[SDL_SCANCODE_E])
			{
				map->Collision(player, 'E');
				this->setActKey(true);
			}
			else if (state[SDL_SCANCODE_W])
			{
				map->Collision(player, 'W');
				this->setActKey(true);
			}
			else if (state[SDL_SCANCODE_A])
			{
				map->Collision(player, 'A');
				this->setActKey(true);
			}
			else if (state[SDL_SCANCODE_D])
			{
				map->Collision(player, 'D');
				this->setActKey(true);
			}
		}
	}
	else if (stare == 2 || stare == 3)
	{
		if (state[SDL_SCANCODE_ESCAPE])
		{
			changeState(stare, 0);
			stare = 0;
		}
	}
	else if (stare == 4 || stare == 5)
	{
		if (state[SDL_SCANCODE_RETURN])
		{
			changeState(stare, 0);
			stare = 0;
		}
	}
}

void Game::update()
{
	if (stare == 1)
	{
		/* Daca tasta a fost apasata, actualieaza direct pozitia player-ului */
		if (this->Key())
		{
			player->update_position();
			this->setActKey(false);
		}
		/* Daca tasta nu a fost apasata, lasa player-ul afectat de gravitatie, apoi actualizeaza pozitia*/
		else
		{
			map->Collision(player, 'S');
			player->update_position();
		}
		/* Daca player-ul castige puncte */
		if (map->GetPoints(player))
		{
			if (points) delete points;
			cnt++;
			char nume[30];
			char nr[2];
			strcpy_s(nume, strlen("data/png/BG/Numbers/") + 1, "data/png/BG/Numbers/");
			_itoa_s(cnt, nr, 10);
			strcat_s(nume, sizeof(nume), nr);
			strcat_s(nume, sizeof(nume), ".png");
			points = new PlaceObject(nume, renderer);
			points->init(100, 0, 50, 50);
		}
		/* Altfel, s-ar putea sa paraseasca harta */
		else if (map->GetOut(player))
		{
			game_data.level = 1;
			changeState(stare, 5);
			stare = 5;
		}
		/* Altfel, s-ar putea sa ajunga la destinatie*/
		else if (map->GetFinish(player))
		{
			if (game_data.level < 5)
			{
				game_data.level++;
				changeState(stare, 1);
				stare = 1;
			}
			else
			{
				game_data.level = 1;
				changeState(stare, 4);
				stare = 4;
			}
		}
		
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	/* Afisez doar background */
	if (stare == 0 || stare == 3 || stare == 4 || stare == 5)
	{
		HomeScreen->draw();
	}
	/* Afisez harta si jucatorul */
	else if (stare == 1)
	{
		map->draw();
		player->draw();
		score->draw();
		points->draw();
	}
	/* Afisez background si detalii joc */
	else if (stare == 2)
	{
		HomeScreen->draw();
		for (uint16_t i = 0; i < totalTime_digits; i++)
		{
			SDL_RenderCopy(renderer, totalTime[i]->objectTex, NULL, &totalTime[i]->srcR);
		}
		for (uint16_t i = 0; i < bestScore_digits; i++)
		{
			SDL_RenderCopy(renderer, bestScore[i]->objectTex, NULL, &bestScore[i]->srcR);
		}
		for (uint16_t i = 0; i < totalScore_digits; i++)
		{
			SDL_RenderCopy(renderer, totalScore[i]->objectTex, NULL, &totalScore[i]->srcR);
		}
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "\n\tINFO: Game was cleaned!...\n";
}