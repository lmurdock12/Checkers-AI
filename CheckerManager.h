#pragma once
#include "Game.h"
class CheckerManager
{
public:

	//what does color do
	CheckerManager(const char* texturesheet_B,const char* texturesheet_R, const char* texturesheet_B_TRANS, const char* texturesheet_R_TRANS
						,const char* texturesheet_B_KING,const char* texturesheet_R_KING, SDL_Renderer* ren, int objHeight, int objWidth, int color);
	~CheckerManager();

	void update_checker(int type, int xpos, int ypos);
	void initBoard();
	void render();

	void move_chip(int type, int xpos, int ypos);
	void remove_chip(int type, int xpos, int ypos);
	bool is_chip(int type, int xpos, int ypos);
	void make_trans(int type, int xpos, int ypos);
	bool any_chip( int xpos, int ypos);
	bool is_king(int type, int xpos, int ypos);
	void make_king(int type, int xpos, int ypos);


private:

	enum {
		GRID_TYPE_NONE = 0,
		GRID_TYPE_B=1, //1
		GRID_TYPE_R=-1, //2
		GRID_TYPE_B_TRANS=2, //3
		GRID_TYPE_R_TRANS=3, //4
		GRID_TYPE_B_KING=4,
		GRID_TYPE_R_KING=5
	
	};

	int current_player;


	//Checker array
	//When making calls to checker array the format is checker_array[ypos][xpos] due to how the array is created
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
	SDL_Texture* objTexture_B_TRANS;
	SDL_Texture* objTexture_R_TRANS;
	SDL_Texture* objTexture_B_KING;
	SDL_Texture* objTexture_R_KING;
};

