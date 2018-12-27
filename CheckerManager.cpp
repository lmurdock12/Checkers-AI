#include "CheckerManager.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

CheckerManager::CheckerManager(const char* texturesheet_B, const char* texturesheet_R, SDL_Renderer* ren, int objHeight, int objWidth, int color)
{
	renderer = ren; //Initialize the renderer to use
	current_player = color; //Initialize which player to start with

	//Size of the checkers
	objH = objHeight;
	objW = objWidth;



	objTexture_B = TextureManager::LoadTexture(texturesheet_B, ren); //Load the texture to use
	srcRect_B.h = objH;
	srcRect_B.w = objW;
	srcRect_B.x = 0;
	srcRect_B.y = 0;

	destRect_B.x = 0;
	destRect_B.y = 0;
	destRect_B.w = srcRect_B.w;
	destRect_B.h = srcRect_B.h;	
	
	
	

	objTexture_R = TextureManager::LoadTexture(texturesheet_R, ren);

	srcRect_R.h = objH;
	srcRect_R.w = objW;
	srcRect_R.x = 0;
	srcRect_R.y = 0;

	destRect_R.x = 0;
	destRect_R.y = 0;
	destRect_R.w = srcRect_B.w;
	destRect_R.h = srcRect_B.h;







	initBoard();


}


CheckerManager::~CheckerManager()
{
}

void CheckerManager::initBoard() {



	for (int i = 0; i < 3; i++) { //rows 0,1,2
		if (i % 2 == 1) {
			for (int j = 0; j < 8; j += 2)
				checker_array[i][j] = GRID_TYPE_R;
		}
		else { //even row
			for (int j = 1; j < 8; j += 2)
				checker_array[i][j] = GRID_TYPE_R;
		}

	}

	

	for (int i = 5; i < 8; i++) { //row
		if (i % 2 == 1) { //odd row
			for (int j = 0; j< 8; j += 2) //column
				checker_array[i][j] = GRID_TYPE_B;
		}
		else { //even row
			for (int j = 1; j < 8; j += 2) //column
				checker_array[i][j] = GRID_TYPE_B;
		}
	}


}



void CheckerManager::update_checker(int type, int xpos, int ypos) {
	if (type == GRID_TYPE_B) {
		destRect_B.x = xpos;
		destRect_B.y = ypos;
	}
	else if (type == GRID_TYPE_R) {
		destRect_R.x = xpos;
		destRect_R.y = ypos;
	}
}



void CheckerManager::move_chip(int type, int xpos, int ypos) {

	if (type == GRID_TYPE_B) {
		checker_array[ypos][xpos] = GRID_TYPE_B;
	}
	else if (type == GRID_TYPE_R){
		checker_array[ypos][xpos] = GRID_TYPE_R;
	}

}


void CheckerManager::render() {



	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (checker_array[i][j] == GRID_TYPE_B) {
				CheckerManager::update_checker(GRID_TYPE_B, j * 100, i * 100);
				SDL_RenderCopy(renderer, objTexture_B, &srcRect_B, &destRect_B);
			}
			else if (checker_array[i][j] == GRID_TYPE_R) {
				CheckerManager::update_checker(GRID_TYPE_R, j * 100, i * 100);
				SDL_RenderCopy(renderer, objTexture_R, &srcRect_R, &destRect_R);

			}


		}
	}
}
