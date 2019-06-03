#include "CheckerManager.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

CheckerManager::CheckerManager(const char* texturesheet_B, const char* texturesheet_R, const char* texturesheet_B_TRANS, const char* texturesheet_R_TRANS, SDL_Renderer* ren, int objHeight, int objWidth, int color)
{
	renderer = ren; //Initialize the renderer to use
	current_player = color; //Initialize which player to start with

	//Size of the checkers
	objH = objHeight;
	objW = objWidth;



	objTexture_B = TextureManager::LoadTexture(texturesheet_B, ren); //Load the texture to use
	objTexture_B_TRANS = TextureManager::LoadTexture(texturesheet_B_TRANS,ren);
	srcRect_B.h = objH;
	srcRect_B.w = objW;
	srcRect_B.x = 0;
	srcRect_B.y = 0;

	destRect_B.x = 0;
	destRect_B.y = 0;
	destRect_B.w = srcRect_B.w;
	destRect_B.h = srcRect_B.h;	
	
	
	

	objTexture_R = TextureManager::LoadTexture(texturesheet_R, ren);
	objTexture_R_TRANS = TextureManager::LoadTexture(texturesheet_R_TRANS, ren);

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
                // Y, X????
	//checker_array[1][4] = GRID_TYPE_B;
	//checker_array[4][1] = GRID_TYPE_R;	

}


//what is the point of this
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

void CheckerManager::make_trans(int type, int xpos, int ypos) {

	if (type == GRID_TYPE_B) {
		checker_array[ypos][xpos] = GRID_TYPE_B_TRANS;
	}
	else if (type == GRID_TYPE_R){
		checker_array[ypos][xpos] = GRID_TYPE_R_TRANS;
	}

}





void CheckerManager::remove_chip(int type, int xpos, int ypos) {

	if (type == GRID_TYPE_B) {
		checker_array[ypos][xpos] = GRID_TYPE_NONE;
	}
	else if (type == GRID_TYPE_R) {
		checker_array[ypos][xpos] = GRID_TYPE_NONE;
	}

}







bool CheckerManager::is_chip(int type, int xpos, int ypos) {

	if (type == GRID_TYPE_B) {
		if (checker_array[ypos][xpos] == GRID_TYPE_B)
			return true;
	}
	else if (type == GRID_TYPE_R) {
		if (checker_array[ypos][xpos] == GRID_TYPE_R)
			return true;
	}
	return false;

}

bool CheckerManager::any_chip( int xpos, int ypos) {

	
		if (!(checker_array[ypos][xpos] == GRID_TYPE_NONE)) {

			return true;
		}

	return false;

}




void CheckerManager::render() {
	//Renders the grid of chips to the screen


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
			else if (checker_array[i][j] == GRID_TYPE_B_TRANS) {
				CheckerManager::update_checker(GRID_TYPE_B, j * 100, i * 100);
				SDL_RenderCopy(renderer, objTexture_B_TRANS,&srcRect_B, &destRect_B);
			}
			else if (checker_array[i][j] == GRID_TYPE_R_TRANS) {
					CheckerManager::update_checker(GRID_TYPE_R, j * 100, i * 100);
					SDL_RenderCopy(renderer, objTexture_R_TRANS,&srcRect_R, &destRect_R);
			}



		}
	}
}

