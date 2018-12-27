#pragma once
#include "SDL.h"
#include "SDL_image.h"


class Game {

public: 


	//Initialize game
	void init(const char* title, int xpos, int ypos, int width, int height,bool fullscreen);

	//HandleEvents();
	void handleEvents();

	//Update events
	void update();

	//Render game
	void render();

	void clean();

	bool running() { return isRunning; }

	static SDL_Renderer *renderer;
	static SDL_Event event;

	enum {
		GRID_TYPE_NONE = 0,
		GRID_TYPE_B,
		GRID_TYPE_R
	};


	//Current Player;
	int current_player;

	//Current Chip
	bool currently_selected;
	int current_xpos;
	int current_ypos;


private:
	
	bool isRunning;
	SDL_Window *window;

\




};




