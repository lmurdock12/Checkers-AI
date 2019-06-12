
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "CheckerManager.h"
#include <iostream>
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

GameObject* board;
CheckerManager* chip_manager;


SDL_Rect srcRect, destRect;
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	int flags = 0;//init the unit32 flag
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN; //if fullscreen is true set the flag to fullscreen
	}
	//Checks to see is SDL library is initialized successfully and prints statement

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) { //If Init() == 0; that means success.
		std::cout << "Subsystems Initialized!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) { //if window is true then it has been successfully created
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 244, 244, 24);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true; //if init works successfully then continue to run
	}
	else {
		isRunning = false; //stop the game if it does not initialize 
	}

	currently_selected = false;

	//Best code I have so far scaling the render on linux to get back to the original size of the png
	//SDL_RenderSetLogicalSize(renderer, 800, 800);
	SDL_RenderSetScale(renderer, 2,2);


	board = new GameObject("assets/checker_board.png", renderer, 0, 0, 800, 800);
	chip_manager = new CheckerManager("assets/checker.png", "assets/red_checker.png", "assets/blue_transparent.png", "assets/red_transparent.png",
										"assets/blue_king.png","assets/red_king.png",renderer, 100, 100, GRID_TYPE_B);
	current_player = GRID_TYPE_B;
	current_cords = new int[2];
	direction = 1;
}

void Game::handleEvents() {

	while (SDL_PollEvent(&event)) { //get the event

		switch (event.type) {
		case SDL_QUIT://if the X is pressed then end the game
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			int x, y;
			//SDL_MouseButtonEvent b = event.button;
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&x, &y);
				int x_cord = (x/100)/2; //Divide by size of square (100) and then divide by 2 since the board is currently doubled to 1600 pixels.
				int y_cord = (y/100)/2;
				std::cout << "X is: " << x_cord << std::endl;
				std::cout << "Y is: " << y_cord << std::endl;
				//std::cout << "Current player is: " << current_player << std::endl;
				//std::cout << "Currently Selected: " << currently_selected << std::endl;

				//If a chip is not currently selected, then see if a valid chip selection is made.
				if (!currently_selected) { Game::select_chip(x_cord, y_cord, current_cords); }


										//GRID_TYPE_B = blue player
				if (current_player == GRID_TYPE_B) {
					//if chip selected and equals grid type B
					//show valid moves
					//determine if move is valid and update chips

					if (currently_selected) {Game::validate_move(x_cord, y_cord, current_cords);} //will be redone
					//at the end of validate move function, run the spot through the select chip function, if a different chip is selected then select that one.
					
				}
				else {

					if (currently_selected) { Game::validate_move(x_cord, y_cord,current_cords); } //will be redone
				}
			}

		default:
			break;
		}
	}
}


void Game::update() {
	//board->Update();

}


void Game::render() {

	SDL_RenderClear(renderer); //clear the renderer

	board->Render();
	chip_manager->render();
	//board->Render();
	SDL_RenderPresent(renderer); //render all the objects

}

void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;

}



void Game::select_chip(int xpos, int ypos, int*& arr) {



	



	//if player selected a valid chip, get the coords and set currently_selected to true
	if (chip_manager->is_chip(current_player, xpos, ypos) && currently_selected == false) {


			//check to see if the chip is a king
				//set kingvar true if it is

			std::cout << "Left: " << chip_manager->any_chip(xpos-1,ypos+1) << std::endl;
			std::cout << "Right: " << chip_manager->any_chip(xpos+1,ypos+1) << std::endl;
			//If the chip is along the left side of rails and there is not a move, then break out of function
			if (xpos==0 && ( ( chip_manager->is_chip(current_player*-1, xpos+1, ypos+(-1*current_player)) &&
					  chip_manager->any_chip(xpos+2, ypos+(-2*current_player))) || chip_manager->is_chip(current_player, xpos+1,ypos+(-1*current_player)) )	) {

						return;
			} else if (xpos==7 && ( (chip_manager->is_chip(current_player*-1, xpos-1, ypos+(-1*current_player)) &&
					  chip_manager->any_chip(xpos-2, ypos+(-2*current_player))) || chip_manager->is_chip(current_player, xpos-1,ypos+(-1*current_player))) ) {
		
						return;
			//if a chip is one spot off the wall and there is no move on the right side and a chip on the left diagonal			
			} else if (xpos==1 && ((chip_manager->is_chip(current_player*-1, xpos+1, ypos+(-1*current_player)) &&			//if same color chip on right side and chip on left diagonal
					  chip_manager->any_chip(xpos+2, ypos+(-2*current_player))) || chip_manager->is_chip(current_player,xpos+1,ypos+(-1*current_player)))
					   && chip_manager->any_chip(xpos-1, ypos+(-1*current_player))) {
						
						return;
			//if a chip is one spot off the wall on left side and there is no right side move and a chip on the right diagonal
			} else if (xpos==6 && ( (chip_manager->is_chip(current_player*-1, xpos-1, ypos+(-1*current_player)) &&			//if same color chip on left side and chip on right diagonal
					  chip_manager->any_chip(xpos-2, ypos+(-2*current_player))) || chip_manager->is_chip(current_player,xpos-1,ypos+(-1*current_player)) )
					  		&& chip_manager->any_chip(xpos+1, ypos+(-1*current_player)) ) {

						return;
			} 
			//ensure there is a spot to move on the last row to become king for blue chip
			else if (ypos==6 && current_player == -1 && ( chip_manager->any_chip(xpos-1,ypos+1) && chip_manager->any_chip(xpos+1,ypos+1)) ) {
						return;
			} 
			//ensure there is a spot to move on the last row to become king for red chip
			else if (ypos==1 && current_player==1 && (chip_manager->any_chip(xpos-1,ypos-1) && chip_manager->any_chip(xpos+1,ypos-1)) ) {
						return;
			}
			//there is some weird functionality with the the two corner spots on the board (row 1 and row 6), the above two if statements show that 100 is stored
			//as the value for the spot that it is trying to determine if there is a chip there or not. It recognizes that the spot is 'technically' not empty
			//and blocks the chip from having to move since there is a chip on the other spot too.



			//if the two diagonal moves are not the current colors chip's
			 else if (!chip_manager->is_chip(current_player, xpos - 1, ypos+(-1*current_player)) 
				|| !chip_manager->is_chip(current_player, xpos + 1, ypos+(-1*current_player))) {



										//if theres NOT an opposite color chip one spot diagonnal left and chip covering the hop spot left
				if(   !(  chip_manager->is_chip(current_player*-1, xpos-1, ypos+(-1*current_player)) &&
					  chip_manager->any_chip(xpos-2, ypos+(-2*current_player)  ) ) ||
					  
					    !( chip_manager->is_chip(current_player*-1, xpos+1, ypos+(-1*current_player)) &&
					  chip_manager->any_chip(xpos+2, ypos+(-2*current_player)) ) ) {

					chip_manager->make_trans(current_player, xpos, ypos);
					currently_selected = true;
					// possible create a seperate transparent function to make easier to read?
					//put move chip function here
					arr[0] = xpos;
					arr[1] = ypos;
				}
				}

/*
					if ( (!chip_manager->is_chip(current_player, xpos-2, ypos+(-2*current_player)) &&
					!chip_manager->is_chip(current_player*-1, xpos-2, ypos+(-2*current_player)) ) ||
						( !chip_manager->is_chip(current_player, xpos+2, ypos+(-2*current_player)) &&
					!chip_manager->is_chip(current_player*-1, xpos+2, ypos+(-2*current_player))) ) {

							chip_manager->make_trans(current_player, xpos, ypos);
							currently_selected = true;
							// possible create a seperate transparent function to make easier to read?
							//put move chip function here
							arr[0] = xpos;
							arr[1] = ypos;
				}




			}
*/

			//need to check diagonal red-->blue's



		/*
		else { //if its a red move

			//if the two diagonal moves are not both red chip's
			if (!chip_manager->is_chip(current_player, xpos - 1, ypos + 1)
				&& !chip_manager->is_chip(current_player, xpos + 1, ypos + 1)) {

				chip_manager->make_trans(current_player, xpos, ypos);
				currently_selected = true;
				arr[0] = xpos;
				arr[1] = ypos;

			}

		}
		*/

		std::cout << "Selected Chip Xpos: " << arr[0] << std::endl;
		std::cout << "Selected Chip Ypos: " << arr[1] << std::endl;
	}



}


void Game::validate_move(int xpos, int ypos,int*& current) {







	// this should all be refractored into differenct functions based on the type of move the validator is checking

	//Determine if the new spot is a valid move
	if (currently_selected)  { // && (current_player == GRID_TYPE_B)) {



		
		//Logic for basic nontakeover left move
		//If left diagonal is selected and there is no red or blue chip located there then move the chip
		//maybe refractor and add a no_chip function instead of calling is_chip twice?						//replace this with any chip
		if (  xpos == current[0]-1 && ypos == current[1]+(-1*current_player) && !chip_manager->is_chip(current_player, current[0]-1, current[1]+(-1*current_player) )
			&& !chip_manager->is_chip(current_player*-1, current[0]-1, current[1]+(-1*current_player)) ) {   

				std::cout << "Current Player:" << current_player << std::endl;
				std::cout << "Blue Chip: " << !(chip_manager->is_chip(current_player, current[0]-1, current[1]+(-1*current_player))) << std::endl;
				std::cout << "Red Chip: " << !chip_manager->is_chip(current_player*-1, current[0]-1, current[1]+(-1*current_player)) << std::endl;


				chip_manager->move_chip(current_player, xpos, ypos); //move chip to new location
				chip_manager->remove_chip(current_player, current[0], current[1]); //remove the old chip

				//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
				chip_manager->make_king(current_player,xpos,ypos);


				currently_selected = false;
				current_player = current_player*-1;

		} else if (  xpos == current[0]+1 && ypos == current[1]+(-1*current_player) && !(chip_manager->is_chip(current_player, current[0]+1, current[1]+(-1*current_player)))
					&& !(chip_manager->is_chip(current_player*-1, current[0]+1, current[1]+(-1*current_player))) ) {

						chip_manager->move_chip(current_player, xpos, ypos); //move chip to new location
						chip_manager->remove_chip(current_player, current[0], current[1]); //remove the old chip

						//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
						chip_manager->make_king(current_player,xpos,ypos);

						currently_selected = false;
						current_player = current_player*-1;

		}

	//potentially replace the current[0] with just like xpos in the certain if statements

		//Logic to check if chip is potential diagonal move spot   (The location the chip will hop to)
		if (((xpos == current[0] - 2) || (xpos == current[0] + 2)) && (ypos == (current[1]+(-2*current_player)))) { //add a chip check here
			//std::cout << "Current_ypos-1: " << current[1] - 1 << std::endl;
			//check to see if the spot currently has a chip of that type


							//opposite chip color one spot to the diagonal left									//mouse click y pos on the hop spot
			if ( (chip_manager->is_chip(current_player*-1, current[0]-1, current[1]+(-1*current_player)) && xpos == current[0]-2) &&
							!chip_manager->any_chip( current[0]-2, current[1]+(-2*current_player)) ) {

				chip_manager->move_chip(current_player, xpos, ypos); //move the chip
				chip_manager->remove_chip(current_player, current[0], current[1]); //remove the old chip
				chip_manager->remove_chip(current_player*-1, current[0]-1, current[1]+(-1*current_player)); //remove opponents chip

				//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
				chip_manager->make_king(current_player,xpos,ypos);

				currently_selected = false;
				current_player = current_player*-1; //switch players


														//opposite chip color one spot to right
			} else if (xpos == current[0]+2 && chip_manager->is_chip(-1*current_player, current[0]+1,current[1]+(-1*current_player)) &&
							!chip_manager->any_chip(current[0]+2, current[1]+(-2*current_player)) ) {

				chip_manager->move_chip(current_player, xpos, ypos); //move the chip
				chip_manager->remove_chip(current_player, current[0], current[1]); //remove the old chip
				chip_manager->remove_chip(current_player*-1, current[0]+1, current[1]+(-1*current_player)); //remove opponents chip  //#

				//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
				chip_manager->make_king(current_player,xpos,ypos);

				currently_selected = false;
				current_player = current_player*-1; //switch players
			}

		}



		//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
		//chip_manager->make_king(current_player*-1,xpos,ypos);



	} 
}