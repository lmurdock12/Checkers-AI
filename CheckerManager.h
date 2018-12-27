#pragma once
#include "Game.h"
class CheckerManager
{
public:
	CheckerManager(const char* texturesheet_B,const char* texturesheet_R, SDL_Renderer* ren, int objHeight, int objWidth, int color);
	~CheckerManager();

	void update_checker(int type, int xpos, int ypos);
	void initBoard();
	void render();

	void move_chip(int type, int xpos, int ypos);
	void remove_chip(int type, int xpos, int ypos);
	bool is_chip(int type, int xpos, int ypos);


private:

	enum {
		GRID_TYPE_NONE = 0,
		GRID_TYPE_B, //1
		GRID_TYPE_R //2
	};

	int current_player;


	//Checker array
	int checker_array[8][8];


	//Data keeping track of width and height
	int objH;
	int objW;


	//Renderer to use
	SDL_Renderer * renderer;
	//Where to place the Blue Checker
	SDL_Rect srcRect_B, destRect_B;

	//Where to place the Red Checker
	SDL_Rect srcRect_R, destRect_R;

	//Texture of the object
	SDL_Texture* objTexture_B;
	SDL_Texture* objTexture_R;
};

