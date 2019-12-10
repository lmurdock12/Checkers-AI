#pragma once
//#include "SDL.h"
//#include "SDL_image.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "CheckerManager.h"
#include <iostream>
#include "AI.h"
#include <random>
class Game {

public: 


	//Initialize game
	void init(const char* title, int xpos, int ypos, int width, int height,bool fullscreen);

	//HandleEvents();
	void handleEvents();

	//Update events
	void update(int val);

	//Render game
	void render();

	void clean();

	bool running() { return isRunning; }

	void updateBlue();

	void initBoard();

	//Funcs that will probably get moved:
	bool select_chip(int xpos, int ypos, int*& current);
	bool validate_move(int xpos, int ypos,int*& current, bool isKing);
	void another_move(int xpos, int ypos, int*& current);
	int check_status();
	int get_winner();
	void getFinalBoard();

	//static SDL_Renderer *renderer;
	//static SDL_Event event;

	enum {
		GRID_TYPE_NONE = 0,
		GRID_TYPE_B=1, //1
		GRID_TYPE_R=-1, //2
		GRID_TYPE_B_TRANS=2, //3
		GRID_TYPE_R_TRANS=3, //4
		GRID_TYPE_B_KING=4,
		GRID_TYPE_R_KING=5,
		GRID_TYPE_B_KING_TRANS=6,
		GRID_TYPE_R_KING_TRANS=7

	
	};

	//Current Player;
	int current_player;
	int direction;
	bool isKing = false;
	int negate = -1;
	int jump_again = false;
	//int render_popup = false;
	bool pop_status = false;
	int* temp_cords;
	int tempx;
	int tempy;
	//Current Chip //probably will get moved
	bool currently_selected;
	int* current_cords;
	bool concurrent;
	bool successfulMove = false;


	SDL_Renderer* renderer = nullptr;
	SDL_Event event;

	//GameObject* board;
	//CheckerManager* chip_manager;


	//SDL_Rect srcRect, destRect;



private:
	
	bool isRunning;
	SDL_Window *window;






};




