#include "CheckerManager.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

CheckerManager::CheckerManager(const char* texturesheet_B, const char* texturesheet_R, const char* texturesheet_B_TRANS, const char* texturesheet_R_TRANS
						,const char* texturesheet_B_KING, const char* texturesheet_R_KING, const char* texturesheet_B_KING_TRANS, const char* texturesheet_R_KING_TRANS, SDL_Renderer* ren, int objHeight, int objWidth, int color)
{
	renderer = ren; //Initialize the renderer to use
	current_player = color; //Initialize which player to start with

	//Size of the checkers
	objH = objHeight;
	objW = objWidth;



	objTexture_B = TextureManager::LoadTexture(texturesheet_B, ren); //Load the texture to use
	objTexture_B_TRANS = TextureManager::LoadTexture(texturesheet_B_TRANS,ren); //Load the transparent chip
	objTexture_B_KING = TextureManager::LoadTexture(texturesheet_B_KING, ren); //Load the king chip
	objTexture_B_KING_TRANS = TextureManager::LoadTexture(texturesheet_B_KING_TRANS, ren); // Loads blue transparent king chip
	objTexture_R_KING_TRANS = TextureManager::LoadTexture(texturesheet_R_KING_TRANS, ren); //Loads red transparent king chip

	srcRect_B.h = objH;
	srcRect_B.w = objW;
	srcRect_B.x = 0;
	srcRect_B.y = 0;

	destRect_B.x = 0;
	destRect_B.y = 0;
	destRect_B.w = srcRect_B.w;
	destRect_B.h = srcRect_B.h;	
	
	
	

	objTexture_R = TextureManager::LoadTexture(texturesheet_R, ren); //Load the texture to use
	objTexture_R_TRANS = TextureManager::LoadTexture(texturesheet_R_TRANS, ren); //Load the transparent chip
	objTexture_R_KING = TextureManager::LoadTexture(texturesheet_R_KING, ren); //Load the king chip

	srcRect_R.h = objH;
	srcRect_R.w = objW;
	srcRect_R.x = 0;
	srcRect_R.y = 0;

	destRect_R.x = 0;
	destRect_R.y = 0;
	destRect_R.w = srcRect_R.w;
	destRect_R.h = srcRect_R.h;


	popup = TextureManager::LoadTexture("assets/continue.png", ren);
	srcRect_pop.h = 200;
	srcRect_pop.w = 400;
	srcRect_pop.x = 0;
	srcRect_pop.y = 0;

	destRect_pop.x = 200;
	destRect_pop.y = 200;
	destRect_pop.h = srcRect_pop.h;
	destRect_pop.w = srcRect_pop.w;



	initBoard();


}


CheckerManager::~CheckerManager()
{
}

void CheckerManager::initBoard() {


	for (int i = 0; i < 3; i++) { //rows 0,1,2
		if (i % 2 == 1) {
			for (int j = 0; j < 8; j += 2) {
				checker_array[i][j] = GRID_TYPE_R;
				checker_array[i][j+1] = GRID_TYPE_NONE;

			}
				
				
		}
		else { //even row
			for (int j = 1; j < 8; j += 2) {
				checker_array[i][j] = GRID_TYPE_R;
				checker_array[i][j-1] = GRID_TYPE_NONE;
			}
		}

	}

	

	for (int i = 5; i < 8; i++) { //row
		if (i % 2 == 1) { //odd row
			for (int j = 0; j< 8; j += 2) {//column
				checker_array[i][j] = GRID_TYPE_B;
				checker_array[i][j+1] = GRID_TYPE_NONE;
			}
		}
		else { //even row
			for (int j = 1; j < 8; j += 2) {//column
				checker_array[i][j] = GRID_TYPE_B;
				checker_array[i][j-1] = GRID_TYPE_NONE;
			}
		}
	}
	
	for (int i=3; i<=4;i++){

		for(int j=0; j<8; j++) {
			checker_array[i][j] = GRID_TYPE_NONE;
		}


	}


                // Y, X????
	//checker_array[5][4] = GRID_TYPE_B_KING;
	//checker_array[4][1] = GRID_TYPE_R_KING;


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



void CheckerManager::move_chip(int type, int xpos, int ypos,int old_x, int old_y, bool& isKing) {
	//std::cout << "move chip type: " << checker_array[old_y][old_x] << std::endl;
	if (type == GRID_TYPE_B) {
		if(checker_array[old_y][old_x] == GRID_TYPE_B_KING_TRANS) {
			checker_array[ypos][xpos] = GRID_TYPE_B_KING;
		} else {
			checker_array[ypos][xpos] = GRID_TYPE_B;			
		}

	}

	else if (type == GRID_TYPE_R){

		if(checker_array[old_y][old_x] == GRID_TYPE_R_KING_TRANS) {
			checker_array[ypos][xpos] = GRID_TYPE_R_KING;
		} else {
			checker_array[ypos][xpos] = GRID_TYPE_R;			
		}
		//checker_array[ypos][xpos] = GRID_TYPE_R;
	}
	isKing = false;
}

void CheckerManager::make_trans(int type, int xpos, int ypos) {

	if (type == GRID_TYPE_B) {
		if (checker_array[ypos][xpos] == GRID_TYPE_B_KING) {
			checker_array[ypos][xpos] = GRID_TYPE_B_KING_TRANS;
		} else {
		checker_array[ypos][xpos] = GRID_TYPE_B_TRANS;
		}
	}
	else if (type == GRID_TYPE_R){
			if(checker_array[ypos][xpos] == GRID_TYPE_R_KING) {
				checker_array[ypos][xpos] = GRID_TYPE_R_KING_TRANS;
				
			} else {

				checker_array[ypos][xpos] = GRID_TYPE_R_TRANS;	
			}

	}

}


void CheckerManager::deselect(int type, int xpos, int ypos) {

	if (type == GRID_TYPE_B) {
		if (checker_array[ypos][xpos] == GRID_TYPE_B_KING_TRANS) {
			checker_array[ypos][xpos] = GRID_TYPE_B_KING;
		} else {
		checker_array[ypos][xpos] = GRID_TYPE_B;
		}
	}
	else if (type == GRID_TYPE_R){
			if(checker_array[ypos][xpos] == GRID_TYPE_R_KING_TRANS) {
				checker_array[ypos][xpos] = GRID_TYPE_R_KING;
				
			} else {

				checker_array[ypos][xpos] = GRID_TYPE_R;	
			}

	}

}



void CheckerManager::remove_chip(int type, int xpos, int ypos) {

	if (type == GRID_TYPE_B) {
		checker_array[ypos][xpos] = GRID_TYPE_NONE;
	}
	else if (type == GRID_TYPE_B_KING) {
		checker_array[ypos][xpos] = GRID_TYPE_NONE;
	}
	else if (type == GRID_TYPE_R) {
		checker_array[ypos][xpos] = GRID_TYPE_NONE;
	}
	else if (type == GRID_TYPE_R_KING) {
		checker_array[ypos][xpos] = GRID_TYPE_NONE;
	}

}


bool CheckerManager::is_chip(int type, int xpos, int ypos) {

	if (type == GRID_TYPE_B || type == GRID_TYPE_B_KING) {
		if (checker_array[ypos][xpos] == GRID_TYPE_B || checker_array[ypos][xpos] == GRID_TYPE_B_KING ||
			checker_array[ypos][xpos] == GRID_TYPE_B_TRANS || checker_array[ypos][xpos] == GRID_TYPE_B_KING_TRANS)
			return true;
	}
	else if (type == GRID_TYPE_R || type == GRID_TYPE_R_KING) {
		if (checker_array[ypos][xpos] == GRID_TYPE_R || checker_array[ypos][xpos] == GRID_TYPE_R_KING ||
			checker_array[ypos][xpos] == GRID_TYPE_R_TRANS || checker_array[ypos][xpos] == GRID_TYPE_R_KING_TRANS)
			return true;
	}
	return false;

}

bool CheckerManager::any_chip( int xpos, int ypos) {

		//std::cout << "chip spot is: " << checker_array[6][7] << std::endl;
		//std::cout << "empty spot is: " << checker_array[7][8] << std::endl;
		//std::cout << "The chip is: " << checker_array[ypos][xpos] << std::endl;
		//
		if (checker_array[ypos][xpos] == GRID_TYPE_B || checker_array[ypos][xpos] == GRID_TYPE_R ||
			checker_array[ypos][xpos] == GRID_TYPE_B_KING || checker_array[ypos][xpos] == GRID_TYPE_R_KING ||
			checker_array[ypos][xpos] == GRID_TYPE_B_TRANS || checker_array[ypos][xpos] == GRID_TYPE_B_KING ||
			checker_array[ypos][xpos] == GRID_TYPE_R_TRANS || checker_array[ypos][xpos] == GRID_TYPE_R_KING_TRANS ||
			ypos < 0 || xpos < 0 || xpos > 7 || ypos > 7){

			return true;
		}

	return false;

}


bool CheckerManager::is_king(int type, int xpos, int ypos) {
	//std::cout << checker_array[ypos][xpos] << std::endl;
	if (type == GRID_TYPE_B) {
		if (checker_array[ypos][xpos] == GRID_TYPE_B_KING) {

			return true;
		} else if (checker_array[ypos][xpos] == GRID_TYPE_B_KING_TRANS)
			return true;
			

	} else if (type == GRID_TYPE_R) {
		if (checker_array[ypos][xpos] == GRID_TYPE_R_KING) {
				return true;
		} else if (checker_array[ypos][xpos] == GRID_TYPE_R_KING_TRANS)
			return true;
	} 
	
	return false;

}

void CheckerManager::make_king(int type, int xpos, int ypos) {


	if(type == GRID_TYPE_B && ypos == 0) {
		checker_array[ypos][xpos] = GRID_TYPE_B_KING;
	} else if (type == GRID_TYPE_R && ypos == 7) {
		checker_array[ypos][xpos] = GRID_TYPE_R_KING;
	}


}

void CheckerManager::enablePopup(bool enab) {

	render_popup = enab;

}

bool CheckerManager::getPopupStatus() {
	return render_popup;
}

void CheckerManager::render() {
	//Renders the grid of chips to the screen

	//std::cout << checker_array << std::endl;
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
			else if (checker_array[i][j] == GRID_TYPE_B_KING) {
				CheckerManager::update_checker(GRID_TYPE_B, j * 100, i * 100);
				SDL_RenderCopy(renderer, objTexture_B_KING,&srcRect_B, &destRect_B);
			}
			else if (checker_array[i][j] == GRID_TYPE_R_KING) {
				CheckerManager::update_checker(GRID_TYPE_R, j * 100, i * 100);
				SDL_RenderCopy(renderer, objTexture_R_KING,&srcRect_R, &destRect_R);
			}
			else if (checker_array[i][j] == GRID_TYPE_B_KING_TRANS) {
				
				CheckerManager::update_checker(GRID_TYPE_B, j * 100, i * 100);
				SDL_RenderCopy(renderer, objTexture_B_KING_TRANS,&srcRect_B, &destRect_B);

			}			
			else if (checker_array[i][j] == GRID_TYPE_R_KING_TRANS) {
				CheckerManager::update_checker(GRID_TYPE_B, j * 100, i * 100);
				SDL_RenderCopy(renderer, objTexture_R_KING_TRANS,&srcRect_B, &destRect_B);

			}
			else if (render_popup) {
				SDL_RenderCopy(renderer, popup, &srcRect_pop, &destRect_pop);
			}


		}
	}
}

