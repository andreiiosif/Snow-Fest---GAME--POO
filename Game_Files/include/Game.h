#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Map.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void changeState(int old_state, int new_state);
	void handleEvents(); /* Primeste informatii despre actiunea jucatorului */
	void update(); /* Actualizeaza derularea jocului */
	void render(); /* Afiseaza pe ecran noile date */
	void clean(); /* Sterge de pe ecran vechile date */

	bool running() { return isRunning; }
	bool Key() { return actKey;  }
	void setActKey(bool x) { actKey = x; };
private:
	game_stats game_data;
	uint32_t cnt = 0;
	uint32_t timestamp = 0; /* Retine timpul scurs intre doua nivele */
	int stare = 0;
	bool isRunning; /* Verifica daca jocul este activ */
	bool actKey; /* Verifica daca la frame-ul curent s-a apasat vreo tasta */
	SDL_Window* window;
	SDL_Renderer* renderer;
};