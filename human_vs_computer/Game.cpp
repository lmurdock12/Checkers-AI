
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "CheckerManager.h"
#include <iostream>
#include "AI.h"
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

GameObject* board;
CheckerManager* chip_manager;


SDL_Rect srcRect, destRect;


vector<int> minimax(AI::Board currentBoard, int depth, bool maximizingPlayer) {
    AI* currPosition;
	vector<int> results;
    if (depth == 0) {
        currPosition = new AI(1,true,-1,currentBoard);
        int score = currPosition->getScore(currPosition->original_board);

		results.clear();
		results.push_back(score);
		results.push_back(0);
        return results; //static evaluation here
    }
    
    if (maximizingPlayer) {
        //set curr player to -1 for reds children
        currPosition = new AI(1,true,-1, currentBoard);
        int maxEval = -1000000;
        int maxPos = -1;
		//std::cout << "curr: " << currPosition->current_player << std::endl;
        for(int i=0; i<currPosition->children.size();i++) {
            int eval = minimax(currPosition->children[i], depth-1, false)[0];
            maxEval = std::max(maxEval, eval);
            if (maxEval == eval) {
                maxPos = i;
            }
        }
        //std::cout << "maxEval: " << maxEval << std::endl;
        //currPosition->getBoard(currPosition->children[maxPos]);

		results.clear();
		results.push_back(maxEval);
		results.push_back(maxPos);
        return results;
        
    } else {

        int minEval = 10000000;
        currPosition = new AI(1,false,1,currentBoard); //Set currPlayer to 1 to get Blues children
        
        for(int i=0; i<currPosition->children.size();i++) {
            int eval = minimax(currPosition->children[i], depth-1, true)[0];
            minEval = std::min(minEval, eval);
        }

		results.clear();
		results.push_back(minEval);
		results.push_back(0);
        return results;
    }



}


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
										"assets/blue_king.png","assets/red_king.png","assets/blue_king_trans.png", "assets/red_king_trans.png",renderer, 100, 100, GRID_TYPE_B);
	current_player = GRID_TYPE_B;
	current_cords = new int[2];
	concurrent = false;
}

void Game::handleEvents() {

	while (SDL_PollEvent(&event)) { //get the event
		switch (event.type) {
		case SDL_QUIT://if the X is pressed then end the game
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			std::cout << "---------------" << std::endl;

			int x, y;
			
			//SDL_MouseButtonEvent b = event.button;
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&x, &y);
				std::cout << "X is: " << x << std::endl;
				std::cout << "Y is: " << y << std::endl;

				
				pop_status = chip_manager->getPopupStatus();
				if (pop_status) {
					if (x>=400 && x <=1200 && y >= 400 && y <= 600) {
							//make another move

							chip_manager->make_trans(current_player, current_cords[0], current_cords[1]);

							chip_manager->enablePopup(false);
							currently_selected = true;
							concurrent = true;
					} else if (x>=400 && x<=1200 && y>=600 && y<=800){
							//switch player
							chip_manager->enablePopup(false);
							currently_selected = false;
							current_player = current_player*-1;
					}


				} else {





				int x_cord = (x/100)/2; //Divide by size of square (100) and then divide by 2 since the board is currently doubled to 1600 pixels.
				int y_cord = (y/100)/2;
				//std::cout << "X is: " << x_cord << std::endl;
				//std::cout << "Y is: " << y_cord << std::endl;


				//If a chip is not currently selected, then see if a valid chip selection is made.
				if (!currently_selected) { 
					negate = -1;
					Game::select_chip(x_cord, y_cord, current_cords);
					//std::cout << "zFirst" << std::endl;
					isKing = chip_manager->is_king(current_player, x_cord, y_cord);
					if (!currently_selected && isKing) {
						//std::cout << "zSecond" << std::endl;
						negate = 1;
						Game::select_chip(x_cord, y_cord, current_cords);
					}


				}


				//std::cout << "Currently selected" << currently_selected << std::endl;
				//if chip selected and equals grid type B
				//show valid moves
				//determine if move is valid and update chips
				
				//std::cout << "KING: " << isKing << std::endl;
				if (currently_selected) {

					//int cont = false; 

					//std::cout << "First" << std::endl;
					negate = -1;
					successfulMove = Game::validate_move(x_cord, y_cord, current_cords, isKing);
					std::cout << successfulMove << std::endl;
					isKing = chip_manager->is_king(current_player,current_cords[0], current_cords[1]);



					if (currently_selected && isKing) {
						std::cout << "Second"<<  std::endl;
						negate = 1;
						successfulMove= Game::validate_move(x_cord, y_cord, current_cords, isKing);

					}

					std::cout << successfulMove << std::endl;

				}

				}




					//at the end of validate move function, run the spot through the select chip function, 
					//if a different chip is selected then select that one.
					

			}

		default:
			break;
		}
	}
}


void Game::update() {
	//board->Update();

	std::cout << "---------------_" << std::endl;
	std::cout << "Successful move: " << successfulMove << std::endl;
	std::cout << "Currently selected: " << currently_selected << std::endl;

	if(successfulMove && !currently_selected) {
		SDL_Delay(1000);
		std::cout << "got a successful move#####" << std::endl;
		successfulMove = false;

		AI* aiTest = new AI(3,true);

		for(int i=0;i<8;i++) {
			for(int j=0;j<8;j++) {

				aiTest->original_board.grid[j][i] = chip_manager->checker_array[j][i]; 
			}
		}

		aiTest->getBoard(aiTest->original_board);

		vector<int> result = minimax(aiTest->original_board,5,true);
		int move_index = result[1];
		int eval = result[0];
		std::cout << "Evaluation func of: " << eval << std::endl;

		aiTest->checker_array = aiTest->original_board;
		aiTest->current_player = -1;
		aiTest->getChildren();
		int size = aiTest->children.size();
		std::cout << "possible moves: " << size << std::endl;
		std::cout << "move index: " << move_index << std::endl;

		aiTest->getBoard(aiTest->children[move_index]);
		
		for(int i=0;i<8;i++) {
			for(int j=0;j<8;j++) {

				chip_manager->checker_array[j][i] = aiTest->children[move_index].grid[j][i];
			}
		}

		currently_selected = false;
		current_player = current_player*-1;
		

	}



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



bool Game::select_chip(int xpos, int ypos, int*& current) {



	if (currently_selected == true) {

		//Logic to check if chip is potential diagonal move spot   (The location the chip will hop to)
		if (((xpos == current[0] - 2) || (xpos == current[0] + 2)) && (ypos == (current[1]+(negate*2*current_player)))) { //add a chip check here
			//std::cout << "Current_ypos-1: " << current[1] - 1 << std::endl;
			//check to see if the spot currently has a chip of that type


							//opposite chip color one spot to the diagonal left									//mouse click y pos on the hop spot
			if ( (chip_manager->is_chip(current_player*-1, current[0]-1, current[1]+(negate*current_player)) && xpos == current[0]-2) &&
							!chip_manager->any_chip( current[0]-2, current[1]+(negate*2*current_player)) ) {



				currently_selected = true;
				// possible create a seperate transparent function to make easier to read?
				//put move chip function here

				//current[0] = xpos;
				//current[1] = ypos;
				return true;
														//opposite chip color one spot to right
			} else if (xpos == current[0]+2 && chip_manager->is_chip(-1*current_player, current[0]+1,current[1]+(negate*current_player)) &&
							!chip_manager->any_chip(current[0]+2, current[1]+(negate*2*current_player)) ) {



				currently_selected = true;
				// possible create a seperate transparent function to make easier to read?
				//put move chip function here
				//current[0] = xpos;
				//current[1] = ypos;
				return true;

			} else {
				return false;
			}
		} else {
			return false;
		}
	}	
	//if player selected a valid chip, get the coords and set currently_selected to true
	 else if (chip_manager->is_chip(current_player, xpos, ypos) && currently_selected == false) {


			//check to see if the chip is a king
				//set kingvar true if it is

			//std::cout << "Left: " << chip_manager->any_chip(xpos-1,ypos+1) << std::endl;
			//std::cout << "Right: " << chip_manager->any_chip(xpos+1,ypos+1) << std::endl;
			//If the chip is along the left side of rails and there is not a move, then break out of function
			if (xpos==0 && ( ( chip_manager->is_chip(current_player*-1, xpos+1, ypos+(negate*current_player)) &&
					  chip_manager->any_chip(xpos+2, ypos+(2*negate*current_player))) || chip_manager->is_chip(current_player, xpos+1,ypos+(negate*current_player)) )	) {

						return false;
			} else if (xpos==7 && ( (chip_manager->is_chip(current_player*-1, xpos-1, ypos+(negate*current_player)) &&
					  chip_manager->any_chip(xpos-2, ypos+(2*negate*current_player))) || chip_manager->is_chip(current_player, xpos-1,ypos+(negate*current_player))) ) {
		
						return false;
			//if a chip is one spot off the wall and there is no move on the right side and a chip on the left diagonal			
			} else if (xpos==1 && ((chip_manager->is_chip(current_player*-1, xpos+1, ypos+(negate*current_player)) &&			//if same color chip on right side and chip on left diagonal
					  chip_manager->any_chip(xpos+2, ypos+(2*negate*current_player))) || chip_manager->is_chip(current_player,xpos+1,ypos+(negate*current_player)))
					   && chip_manager->any_chip(xpos-1, ypos+(negate*current_player))) {
						
						return false;
			//if a chip is one spot off the wall on left side and there is no right side move and a chip on the right diagonal
			} else if (xpos==6 && ( (chip_manager->is_chip(current_player*-1, xpos-1, ypos+(negate*current_player)) &&			//if same color chip on left side and chip on right diagonal
					  chip_manager->any_chip(xpos-2, ypos+(2*negate*current_player))) || chip_manager->is_chip(current_player,xpos-1,ypos+(negate*current_player)) )
					  		&& chip_manager->any_chip(xpos+1, ypos+(negate*current_player)) ) {

						return false;
			} 
			//ensure there is a spot to move on the last row to become king for blue chip
			else if (ypos==6 && current_player == -1 && ( chip_manager->any_chip(xpos-1,ypos+1) && chip_manager->any_chip(xpos+1,ypos+1))
						&& !chip_manager->is_king(current_player,xpos,ypos) ) {
						return false;
			} 
			//ensure there is a spot to move on the last row to become king for red chip
			else if (ypos==1 && current_player==1 && (chip_manager->any_chip(xpos-1,ypos-1) && chip_manager->any_chip(xpos+1,ypos-1)) 
							&& !chip_manager->is_king(current_player,xpos,ypos)) {
						return false;
			}
			//there is some weird functionality with the the two corner spots on the board (row 1 and row 6), the above two if statements show that 100 is stored
			//as the value for the spot that it is trying to determine if there is a chip there or not. It recognizes that the spot is 'technically' not empty
			//and blocks the chip from having to move since there is a chip on the other spot too.
			
			//If the two diagonal spots are the same color as the chip then return since no move possible.
			 else if (chip_manager->is_chip(current_player, xpos-1, ypos+(negate*current_player)) && 
					chip_manager->is_chip(current_player, xpos+1, ypos+(negate*current_player))) {

					return false;
			}
			 
			//If there is a an opposite color chip on the diagonal left and no hop move possible then return
			else if (  (chip_manager->is_chip(current_player*-1, xpos-1, ypos+(negate*current_player)) &&
					  chip_manager->any_chip(xpos-2, ypos+(2*negate*current_player)  ) ) && 
					  //If there is a an opposite color chip on the diagonal right and no hop move possible then return
					  ( chip_manager->is_chip(current_player*-1, xpos+1, ypos+(negate*current_player)) &&
						chip_manager->any_chip(xpos+2, ypos+(2*negate*current_player)) ) ){
						
					return false;
			}
			 
			else if (chip_manager->is_chip(current_player*-1, xpos-1, ypos+(negate*current_player)) && chip_manager->any_chip(xpos-2, ypos+(2*negate*current_player)) &&
						chip_manager->is_chip(current_player,xpos+1, ypos+(negate*current_player))   ) {
							return false;
			}
			else if (chip_manager->is_chip(current_player*-1, xpos+1, ypos+(negate*current_player)) && chip_manager->any_chip(xpos+2, ypos+(2*negate*current_player)) &&
						chip_manager->is_chip(current_player, xpos-1, ypos+(negate*current_player))  		) {
						return false;
			}	
			
			else {

				chip_manager->make_trans(current_player, xpos, ypos);
				currently_selected = true;
				// possible create a seperate transparent function to make easier to read?
				//put move chip function here
				current[0] = xpos;
				current[1] = ypos;
				return true;


			}

		//std::cout << "Selected Chip Xpos: " << current[0] << std::endl;
		//std::cout << "Selected Chip Ypos: " << current[1] << std::endl;
	


		}

		else {
			return false;
		}

	
	}





bool Game::validate_move(int xpos, int ypos,int*& current, bool isKing) {



	//std::cout << "Current player: " << current_player << std::endl;
	//std::cout << "Negate val: " << negate << std::endl;
	//std::cout << "ANYCHIP: " << chip_manager->any_chip(current[0]+2, current[1]+(negate*2*current_player)) << std::endl;

	// this should all be refractored into differenct functions based on the type of move the validator is checking

	//Determine if the new spot is a valid move
	if (currently_selected)  { // && (current_player == GRID_TYPE_B)) {



		
		//Logic for basic nontakeover left move
		//If left diagonal is selected and there is no red or blue chip located there then move the chip
		//maybe refractor and add a no_chip function instead of calling is_chip twice?						//replace this with any chip
		if (  xpos == current[0]-1 && ypos == current[1]+(negate*current_player) && !chip_manager->is_chip(current_player, current[0]-1, current[1]+(negate*current_player) )
			&& !chip_manager->is_chip(current_player*-1, current[0]-1, current[1]+(negate*current_player)) && !concurrent) {   

				//std::cout << "Current Player:" << current_player << std::endl;
				//std::cout << "Blue Chip: " << !(chip_manager->is_chip(current_player, current[0]-1, current[1]+(-1*current_player))) << std::endl;
				//std::cout << "Red Chip: " << !chip_manager->is_chip(current_player*-1, current[0]-1, current[1]+(-1*current_player)) << std::endl;
	
				
				chip_manager->move_chip(current_player, xpos, ypos, current[0], current[1], isKing); //move chip to new location
				
				
				chip_manager->remove_chip(current_player, current[0], current[1]); //remove the old chip

				//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
				chip_manager->make_king(current_player,xpos,ypos);


				currently_selected = false;
				current_player = current_player*-1;
				return true;

		} else if (  xpos == current[0]+1 && ypos == current[1]+(negate*current_player) && !(chip_manager->is_chip(current_player, current[0]+1, current[1]+(negate*current_player)))
					&& !(chip_manager->is_chip(current_player*-1, current[0]+1, current[1]+(negate*current_player))) && !concurrent) {

						chip_manager->move_chip(current_player, xpos, ypos, current[0], current[1], isKing); //move chip to new location
						chip_manager->remove_chip(current_player, current[0], current[1]); //remove the old chip

						//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
						chip_manager->make_king(current_player,xpos,ypos);


						currently_selected = false;
						current_player = current_player*-1;
						return true;

		}

	//potentially replace the current[0] with just like xpos in the certain if statements

		//Logic to check if chip is potential diagonal move spot   (The location the chip will hop to)
		if (((xpos == current[0] - 2) || (xpos == current[0] + 2)) && (ypos == (current[1]+(negate*2*current_player)))) { //add a chip check here
			//std::cout << "Current_ypos-1: " << current[1] - 1 << std::endl;
			//check to see if the spot currently has a chip of that type


							//opposite chip color one spot to the diagonal left									//mouse click y pos on the hop spot
			if ( (chip_manager->is_chip(current_player*-1, current[0]-1, current[1]+(negate*current_player)) && xpos == current[0]-2) &&
							!chip_manager->any_chip( current[0]-2, current[1]+(negate*2*current_player)) ) {

				chip_manager->move_chip(current_player, xpos, ypos, current[0], current[1], isKing); //move the chip
				chip_manager->remove_chip(current_player, current[0], current[1]); //remove the old chip
				chip_manager->remove_chip(current_player*-1, current[0]-1, current[1]+(negate*current_player)); //remove opponents chip

				//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
				chip_manager->make_king(current_player,xpos,ypos);

				//Update the new current spot:
				current[0] = xpos;
				current[1] = ypos;
				
				isKing = chip_manager->is_king(current_player,current_cords[0], current_cords[1]);

				//Refractor the right diagonal (else) code to be like this for checking double hop
				if ( (Game::select_chip(current_cords[0]-2,current_cords[1]+(2*negate*current_player), current_cords) ||
					Game::select_chip(current_cords[0]+2,current_cords[1]+(2*negate*current_player), current_cords)) ){
					//(Game::select_chip(current_cords[0]+2,current_cords[1]+(2*negate*-1*current_player), current_cords)	||
						//Game::select_chip(current_cords[0]-2,current_cords[1]+(2*negate*-1*current_player), current_cords)) ) {
						//currently_selected = true;
						//render_popup = true;
						chip_manager->enablePopup(true);
						return false;



					}
					else if (isKing) {


						negate *= -1;
						if ((Game::select_chip(current_cords[0]-2, current_cords[1]+(2*negate*current_player),current_cords) ||
						Game::select_chip(current_cords[0]+2, current_cords[1]+(2*negate*current_player),current_cords))) {
								
								negate *= -1;
								chip_manager->enablePopup(true);
								return false;


						} 
						negate *= -1;

					}
				currently_selected = false;
				current_player = current_player*-1;
				concurrent = false;
				return true;
				//current_player = current_player*-1; //switch players


														//opposite chip color one spot to right
			} else if (xpos == current[0]+2 && chip_manager->is_chip(-1*current_player, current[0]+1,current[1]+(negate*current_player)) &&
							!chip_manager->any_chip(current[0]+2, current[1]+(negate*2*current_player)) ) {


						
				chip_manager->move_chip(current_player, xpos, ypos, current[0], current[1], isKing); //move the chip
				chip_manager->remove_chip(current_player, current[0], current[1]); //remove the old chip
				chip_manager->remove_chip(current_player*-1, current[0]+1, current[1]+(negate*current_player)); //remove opponents chip  //#

				//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
				chip_manager->make_king(current_player,xpos,ypos);




				//Update the new current spot:
				current[0] = xpos;
				current[1] = ypos;
				//set the current chip location to the recently moved spot
				isKing = chip_manager->is_king(current_player,current_cords[0], current_cords[1]);

					if (Game::select_chip(current_cords[0]-2,current_cords[1]+(2*negate*current_player), current_cords) ||
					Game::select_chip(current_cords[0]+2,current_cords[1]+(2*negate*current_player), current_cords))  {
						//currently_selected = true;
						chip_manager->enablePopup(true);
						return false;
						
					}
					else if (isKing) {
						//Try negating the player to try the two other current possibilities
						
						negate *= -1;
						if ((Game::select_chip(current_cords[0]-2, current_cords[1]+(2*negate*current_player),current_cords) ||
						Game::select_chip(current_cords[0]+2, current_cords[1]+(2*negate*current_player),current_cords))) {
								
								negate *= -1;
								chip_manager->enablePopup(true);
								return false;


						} 
						negate *= -1;
					}
					currently_selected = false;
					current_player = current_player*-1;
					concurrent = false;
					return true;	
		

				
			}


			}



		}

	//If a chip is currently selected and the double hop prompt is not displayed or no double hop is currently
	//going on then see if the chip selected is potentially a different valid move
	if (currently_selected && !pop_status && !concurrent) {

		if ( chip_manager->is_chip(current_player, xpos, ypos) && (xpos != current[0] || ypos != current[1])) {
				//use temp array here;
				tempx = current[0];
				tempy = current[1];

				//Game::temp_cords[0] = xpos;
				//Game::temp_cords[1] = ypos;
				currently_selected = false;
				if (!(Game::select_chip(xpos,ypos, current_cords)) ){
					
					currently_selected = true;
				} else {
					chip_manager->deselect(current_player,tempx,tempy);
				}



	} else {
		return false;
	}
	}
}


	//chip_manager->is_king(current_player, current[0], current[1]) 
	//Check if king
	/* 
	if (chip_manager->is_king(current_player, current[0], current[1]) && currently_selected == true) {
		negate = 1;
		std::cout << "GOT HERE"<<  std::endl;
		Game::validate_move(xpos, ypos, current);
	} else {
		negate = -1;
	}
	*/



void Game::another_move(int xpos, int ypos, int*& current){

		if (((xpos == current[0] - 2) || (xpos == current[0] + 2)) && (ypos == (current[1]+(negate*2*current_player)))) { //add a chip check here
			//std::cout << "Current_ypos-1: " << current[1] - 1 << std::endl;
			//check to see if the spot currently has a chip of that type


							//opposite chip color one spot to the diagonal left									//mouse click y pos on the hop spot
			if ( (chip_manager->is_chip(current_player*-1, current[0]-1, current[1]+(negate*current_player)) && xpos == current[0]-2) &&
							!chip_manager->any_chip( current[0]-2, current[1]+(negate*2*current_player)) ) {

				chip_manager->move_chip(current_player, xpos, ypos, current[0], current[1], isKing); //move the chip
				chip_manager->remove_chip(current_player, current[0], current[1]); //remove the old chip
				chip_manager->remove_chip(current_player*-1, current[0]-1, current[1]+(negate*current_player)); //remove opponents chip

				//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
				chip_manager->make_king(current_player,xpos,ypos);

				currently_selected = false;
				current_player = current_player*-1; //switch players


														//opposite chip color one spot to right
			} else if (xpos == current[0]+2 && chip_manager->is_chip(-1*current_player, current[0]+1,current[1]+(negate*current_player)) &&
							!chip_manager->any_chip(current[0]+2, current[1]+(negate*2*current_player)) ) {


						
				chip_manager->move_chip(current_player, xpos, ypos, current[0], current[1], isKing); //move the chip
				chip_manager->remove_chip(current_player, current[0], current[1]); //remove the old chip
				chip_manager->remove_chip(current_player*-1, current[0]+1, current[1]+(negate*current_player)); //remove opponents chip  //#

				//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
				chip_manager->make_king(current_player,xpos,ypos);

				currently_selected = false;
				current_player = current_player*-1; //switch players
			}

		}

}