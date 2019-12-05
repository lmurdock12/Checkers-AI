#include "AI.h"
#include <iostream>
#include <vector>

using std::vector;






AI::AI(int depth, bool player_turn, int currPlayer, AI::Board check_arr) {
	curr_depth = depth;
	player = player_turn;

	original_board = check_arr;
	checker_array = original_board;

	current_player = currPlayer;
	
	getChildren();
}

AI::AI(int depth, bool player) {
	curr_depth = depth;
	player = player;

}

int AI::getScore(AI::Board board) {

	int B_count = 0;
	int R_count = 0;

    for (int i=0; i<8;i++) { //Loop through rows
        for (int j=0; j<8; j++) { //Loop through columns
            if (board.grid[i][j] == GRID_TYPE_B) {
                B_count += 1;
            }
            if (board.grid[i][j] == GRID_TYPE_R) {
                R_count += 1;
            }
            if (board.grid[i][j] == GRID_TYPE_B_KING) {
                B_count += 1;
            }
            if (board.grid[i][j] == GRID_TYPE_R_KING) {
                R_count += 1;
            }
        }
    }

	return R_count - B_count;
}


void AI::getChildren() {

    
    //std::cout << "Main file test" << std::endl;

    //aiTest->getBoard(boards);

    int* current;
    //aiTest->get_current(current);

    //std::cout << "Original board: " << std::endl;
    //getBoard();

    for(int i=0; i<8; i++) {
            //std::cout << "next row" << std::endl;
        for(int j=0; j<8; j++) {
            //std::cout << "next column" << std::endl;
            set_currently_selected(false);
            current = getCurrentCordsVar(); //Get the current value of 
            bool foundMove = false;

			checker_array = original_board;
            //aiTest->getBoard();
            //See if current cords is a selectable chip
            if(select_chip(j,i,current)) {

                //std::cout << "got selection X: " << j << ", Y: " << i << std::endl;
                //Get the current cords of selected chip
                //current = aiTest->getCurrentCordsVar();
                //if valid move was made print the updated board
				isKing = is_king(current_player,j,i);

                if(!validate_move(current[0]-1,current[1]+(negate*current_player),current,isKing)) {

                    //std::cout << "got move" << std::endl;
					children.push_back(checker_array);
                    //getBoard();
                    checker_array = original_board;
					make_trans(current_player,j,i);
                    set_currently_selected(true);
                    foundMove = true;

                }
                //std::cout << "current board is: " <<std::endl;
                //aiTest->getBoard(boards);
                if (!validate_move(current[0]+1,current[1]+(negate*current_player),current,isKing)) {
                    //std::cout << "got move" << std::endl;
                    children.push_back(checker_array);
                    //getBoard();
                    checker_array = original_board;
					make_trans(current_player,j,i);
                    set_currently_selected(true);
                    foundMove = true;

                } 
                if(!validate_move(current[0]-2,current[1]+(negate*current_player*2),current,isKing)) {

                    //std::cout << "got move" << std::endl;
                    children.push_back(checker_array);
                    //getBoard();
                    checker_array = original_board;
					make_trans(current_player,j,i);
                    set_currently_selected(true);
                    foundMove = true;

                }
                if(!validate_move(current[0]+2,current[1]+(negate*current_player*2),current,isKing)) {
                    //std::cout << "got move" << std::endl;
                    children.push_back(checker_array);
                    //getBoard();
                    checker_array = original_board;
					make_trans(current_player,j,i);
                    set_currently_selected(true);
                    foundMove = true;


                }


				if(isKing) {

					negate *= -1;
					if(!validate_move(current[0]-1,current[1]+(negate*current_player),current,isKing)) {

						//std::cout << "got move" << std::endl;
						children.push_back(checker_array);
						//getBoard();
						checker_array = original_board;
						make_trans(current_player,j,i);
						set_currently_selected(true);
						foundMove = true;

					}
					//std::cout << "current board is: " <<std::endl;
					//aiTest->getBoard(boards);
					if (!validate_move(current[0]+1,current[1]+(negate*current_player),current,isKing)) {
						//std::cout << "got move" << std::endl;
						children.push_back(checker_array);
						//getBoard();
						checker_array = original_board;
						make_trans(current_player,j,i);
						set_currently_selected(true);
						foundMove = true;

					} 
					if(!validate_move(current[0]-2,current[1]+(negate*current_player*2),current,isKing)) {

						//std::cout << "got move" << std::endl;
						children.push_back(checker_array);
						//getBoard();
						checker_array = original_board;
						make_trans(current_player,j,i);
						set_currently_selected(true);
						foundMove = true;

					}
					if(!validate_move(current[0]+2,current[1]+(negate*current_player*2),current,isKing)) {
						//std::cout << "got move" << std::endl;
						children.push_back(checker_array);
						//getBoard();
						checker_array = original_board;
						make_trans(current_player,j,i);
						set_currently_selected(true);
						foundMove = true;

					}
					negate *= -1;



				}


                if (foundMove == false) {
                    //std::cout << "did not find move" << std::endl;
                }
                set_currently_selected(false);

            }

            //If a chip was selected check the following to see if a valid move.
                //simple left, right
                //hop left, right

            //loop through new boards and see if that board is in the list
            //if not in the list then add the board to the list.
            
        }

    }	

	//std::cout << children.size() << std::endl;

}

void AI::initBoard() {

	for (int i = 0; i < 3; i++) { //rows 0,1,2
		if (i % 2 == 1) {
			for (int j = 0; j < 8; j += 2) {
				checker_array.grid[i][j] = GRID_TYPE_R;
				checker_array.grid[i][j+1] = GRID_TYPE_NONE;

			}
				
				
		}
		else { //even row
			for (int j = 1; j < 8; j += 2) {
				checker_array.grid[i][j] = GRID_TYPE_R;
				checker_array.grid[i][j-1] = GRID_TYPE_NONE;
			}
		}

	}

	

	for (int i = 5; i < 8; i++) { //row
		if (i % 2 == 1) { //odd row
			for (int j = 0; j< 8; j += 2) {//column
				checker_array.grid[i][j] = GRID_TYPE_NONE;
				checker_array.grid[i][j+1] = GRID_TYPE_NONE;
			}
		}
		else { //even row
			for (int j = 1; j < 8; j += 2) {//column
				checker_array.grid[i][j] = GRID_TYPE_NONE;
				checker_array.grid[i][j-1] = GRID_TYPE_NONE;
			}
		}
	}
	
	for (int i=3; i<=4;i++){

		for(int j=0; j<8; j++) {
			checker_array.grid[i][j] = GRID_TYPE_NONE;
		}


	}
	
	checker_array.grid[3][2] = GRID_TYPE_B;
	checker_array.grid[5][4] = GRID_TYPE_B;
	/*
	checker_array.grid[3][0] = GRID_TYPE_R;
	checker_array.grid[3][6] = GRID_TYPE_R;
	checker_array.grid[4][1] = GRID_TYPE_B;
	checker_array.grid[4][3] = GRID_TYPE_B;
	checker_array.grid[4][5] = GRID_TYPE_B;
	checker_array.grid[5][2] = GRID_TYPE_NONE;
	checker_array.grid[5][6] = GRID_TYPE_NONE;
	checker_array.grid[6][5] = GRID_TYPE_NONE;*/


    //current_cords = new int[2];
                // Y, X????
	//checker_array.grid[4][1] = GRID_TYPE_R;
	//checker_array[4][1] = GRID_TYPE_R_KING;
	//checker_array{}

}

AI::Board AI::returnBoard() {
	return checker_array;
}

int* AI::getCurrentCordsVar() {

    return current_cords;

}

void AI::getBoard(AI::Board board) {

    std::cout << "################" << std::endl;

    for (int i=0; i<8;i++) { //Loop through rows

        for (int j=0; j<8; j++) { //Loop through columns

            if (board.grid[i][j] == GRID_TYPE_NONE) {
                std::cout << "_";
            }
            if (board.grid[i][j] == GRID_TYPE_B) {
                std::cout << "B";
            }
            if (board.grid[i][j] == GRID_TYPE_R) {
                std::cout << "R";
            }
            if (board.grid[i][j] == GRID_TYPE_B_KING) {
                std::cout << "K";
            }
            if (board.grid[i][j] == GRID_TYPE_R_KING) {
                std::cout << "K";
            }
            std::cout << " ";
        }
        std::cout << std::endl;

    }
    std::cout << "################" << std::endl;


}



bool AI::is_chip(int type, int xpos, int ypos) {

	if (type == GRID_TYPE_B || type == GRID_TYPE_B_KING) {
		if (checker_array.grid[ypos][xpos] == GRID_TYPE_B || checker_array.grid[ypos][xpos] == GRID_TYPE_B_KING ||
			checker_array.grid[ypos][xpos] == GRID_TYPE_B_TRANS || checker_array.grid[ypos][xpos] == GRID_TYPE_B_KING_TRANS)
			return true;
	}
	else if (type == GRID_TYPE_R || type == GRID_TYPE_R_KING) {
		if (checker_array.grid[ypos][xpos] == GRID_TYPE_R || checker_array.grid[ypos][xpos] == GRID_TYPE_R_KING ||
			checker_array.grid[ypos][xpos] == GRID_TYPE_R_TRANS || checker_array.grid[ypos][xpos] == GRID_TYPE_R_KING_TRANS)
			return true;
	}
	return false;

}

bool AI::is_king(int type, int xpos, int ypos) {
	//std::cout << checker_array[ypos][xpos] << std::endl;
	if (type == GRID_TYPE_B) {
		if (checker_array.grid[ypos][xpos] == GRID_TYPE_B_KING) {

			return true;
		} else if (checker_array.grid[ypos][xpos] == GRID_TYPE_B_KING_TRANS)
			return true;
			

	} else if (type == GRID_TYPE_R) {
		if (checker_array.grid[ypos][xpos] == GRID_TYPE_R_KING) {
				return true;
		} else if (checker_array.grid[ypos][xpos] == GRID_TYPE_R_KING_TRANS)
			return true;
	} 
	
	return false;

}

bool AI::any_chip( int xpos, int ypos) {

		//std::cout << "chip spot is: " << checker_array[6][7] << std::endl;
		//std::cout << "empty spot is: " << checker_array[7][8] << std::endl;
		//std::cout << "The chip is: " << checker_array[ypos][xpos] << std::endl;
		//
		if (checker_array.grid[ypos][xpos] == GRID_TYPE_B || checker_array.grid[ypos][xpos] == GRID_TYPE_R ||
			checker_array.grid[ypos][xpos] == GRID_TYPE_B_KING || checker_array.grid[ypos][xpos] == GRID_TYPE_R_KING ||
			checker_array.grid[ypos][xpos] == GRID_TYPE_B_TRANS || checker_array.grid[ypos][xpos] == GRID_TYPE_B_KING ||
			checker_array.grid[ypos][xpos] == GRID_TYPE_R_TRANS || checker_array.grid[ypos][xpos] == GRID_TYPE_R_KING_TRANS ||
			ypos < 0 || xpos < 0 || xpos > 7 || ypos > 7){

			return true;
		}

	return false;

}

void AI::get_current(int*& current) {

    std::cout << "Current Xpos is: " << current[0] << std::endl;
    std::cout << "Current Ypos is: " << current[1] << std::endl;
    
}

void AI::set_currently_selected(bool var) {

    currently_selected = var;

}

bool AI::select_chip(int xpos, int ypos, int*& current) {



	if (currently_selected == true) {

		//Logic to check if chip is potential diagonal move spot   (The location the chip will hop to)
		if (((xpos == current[0] - 2) || (xpos == current[0] + 2)) && (ypos == (current[1]+(negate*2*current_player)))) { //add a chip check here
			//std::cout << "Current_ypos-1: " << current[1] - 1 << std::endl;
			//check to see if the spot currently has a chip of that type


							//opposite chip color one spot to the diagonal left									//mouse click y pos on the hop spot
			if ( (is_chip(current_player*-1, current[0]-1, current[1]+(negate*current_player)) && xpos == current[0]-2) &&
							!any_chip( current[0]-2, current[1]+(negate*2*current_player)) ) {



				currently_selected = true;
				// possible create a seperate transparent function to make easier to read?
				//put move chip function here

				//current[0] = xpos;
				//current[1] = ypos;
				return true;
														//opposite chip color one spot to right
			} else if (xpos == current[0]+2 && is_chip(-1*current_player, current[0]+1,current[1]+(negate*current_player)) &&
							!any_chip(current[0]+2, current[1]+(negate*2*current_player)) ) {



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
	 else if (is_chip(current_player, xpos, ypos) && currently_selected == false) {

			 /*
		 	if (is_chip(current_player,xpos,ypos)) {
				 std::cout << "Current player chip of type: " << current_player << ", X: " << xpos << ", Y: " << ypos << std::endl;
			 }*/
			//check to see if the chip is a king
				//set kingvar true if it is

			//std::cout << "Left: " << chip_manager->any_chip(xpos-1,ypos+1) << std::endl;
			//std::cout << "Right: " << chip_manager->any_chip(xpos+1,ypos+1) << std::endl;
			//If the chip is along the left side of rails and there is not a move, then break out of function
								//opposite color chip one spot to right
			if (xpos==0 && ( ( is_chip(current_player*-1, xpos+1, ypos+(negate*current_player)) &&
						//anychip covering hop spot								//same color chip on right
					  any_chip(xpos+2, ypos+(2*negate*current_player))) || is_chip(current_player, xpos+1,ypos+(negate*current_player)) )	) {

						return false;
			} else if (xpos==7 && ( (is_chip(current_player*-1, xpos-1, ypos+(negate*current_player)) &&
					  any_chip(xpos-2, ypos+(2*negate*current_player))) || is_chip(current_player, xpos-1,ypos+(negate*current_player))) ) {
		
						return false;
			//if a chip is one spot off the wall and there is no move on the right side and a chip on the left diagonal			
			} else if (xpos==1 && ((is_chip(current_player*-1, xpos+1, ypos+(negate*current_player)) &&			//if same color chip on right side and chip on left diagonal
					  any_chip(xpos+2, ypos+(2*negate*current_player))) || is_chip(current_player,xpos+1,ypos+(negate*current_player)))
					   && any_chip(xpos-1, ypos+(negate*current_player))) {
						
						return false;
			//if a chip is one spot off the wall on left side and there is no right side move and a chip on the right diagonal
			} else if (xpos==6 && ( (is_chip(current_player*-1, xpos-1, ypos+(negate*current_player)) &&			//if same color chip on left side and chip on right diagonal
					  any_chip(xpos-2, ypos+(2*negate*current_player))) || is_chip(current_player,xpos-1,ypos+(negate*current_player)) )
					  		&& any_chip(xpos+1, ypos+(negate*current_player)) ) {

						return false;
			} 
			//ensure there is a spot to move on the last row to become king for blue chip
			else if (ypos==6 && current_player == -1 && ( any_chip(xpos-1,ypos+1) && any_chip(xpos+1,ypos+1))
						&& !is_king(current_player,xpos,ypos) ) {
						return false;
			} 
			//ensure there is a spot to move on the last row to become king for red chip
			else if (ypos==1 && current_player==1 && (any_chip(xpos-1,ypos-1) && any_chip(xpos+1,ypos-1)) 
							&& !is_king(current_player,xpos,ypos)) {
						return false;
			}
			//there is some weird functionality with the the two corner spots on the board (row 1 and row 6), the above two if statements show that 100 is stored
			//as the value for the spot that it is trying to determine if there is a chip there or not. It recognizes that the spot is 'technically' not empty
			//and blocks the chip from having to move since there is a chip on the other spot too.
			
			//If the two diagonal spots are the same color as the chip then return since no move possible.
			 else if (is_chip(current_player, xpos-1, ypos+(negate*current_player)) && 
					is_chip(current_player, xpos+1, ypos+(negate*current_player))) {

					return false;
			}
			 
			//If there is a an opposite color chip on the diagonal left and no hop move possible then return
			else if (  (is_chip(current_player*-1, xpos-1, ypos+(negate*current_player)) &&
					  any_chip(xpos-2, ypos+(2*negate*current_player)  ) ) && 
					  //If there is a an opposite color chip on the diagonal right and no hop move possible then return
					  ( is_chip(current_player*-1, xpos+1, ypos+(negate*current_player)) &&
						any_chip(xpos+2, ypos+(2*negate*current_player)) ) ){
						
					return false;
			}
			 
			else if (is_chip(current_player*-1, xpos-1, ypos+(negate*current_player)) && any_chip(xpos-2, ypos+(2*negate*current_player)) &&
						is_chip(current_player,xpos+1, ypos+(negate*current_player))   ) {
							return false;
			}
			else if (is_chip(current_player*-1, xpos+1, ypos+(negate*current_player)) && any_chip(xpos+2, ypos+(2*negate*current_player)) &&
						is_chip(current_player, xpos-1, ypos+(negate*current_player))  		) {
						return false;
			}	
			
			else {

                //std::cout << "GOT A SELECTION" << std::endl;
				//////make_trans(current_player, xpos, ypos);
				make_trans(current_player, xpos, ypos);
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


bool AI::validate_move(int xpos, int ypos,int*& current, bool isKing) {



	//std::cout << "Current player: " << current_player << std::endl;
	////std::cout << "Negate val: " << negate << std::endl;
	////std::cout << "ANYCHIP: " << chip_manager->any_chip(current[0]+2, current[1]+(negate*2*current_player)) << std::endl;

	// this should all be refractored into differenct functions based on the type of move the validator is checking

	//Determine if the new spot is a valid move
	if (currently_selected && xpos < 8  && xpos >=0 && ypos < 8 and ypos >= 0)  { // && (current_player == GRID_TYPE_B)) {

		//Logic for basic nontakeover left move
		//If left diagonal is selected and there is no red or blue chip located there then move the chip
		//maybe refractor and add a no_chip function instead of calling is_chip twice?						//replace this with any chip
		if (  xpos == current[0]-1 && ypos == current[1]+(negate*current_player) && !is_chip(current_player, current[0]-1, current[1]+(negate*current_player) )
			&& !is_chip(current_player*-1, current[0]-1, current[1]+(negate*current_player)) && xpos >= 0 && xpos <=7  ) {   

				//std::cout << "Current Player:" << current_player << std::endl;
				//std::cout << "Blue Chip: " << !(chip_manager->is_chip(current_player, current[0]-1, current[1]+(-1*current_player))) << std::endl;
				//std::cout << "Red Chip: " << !chip_manager->is_chip(current_player*-1, current[0]-1, current[1]+(-1*current_player)) << std::endl;
	
				
				move_chip(current_player, xpos, ypos, current[0], current[1], isKing); //move chip to new location
				
				
				remove_chip(current_player, current[0], current[1]); //remove the old chip

				//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
				make_king(current_player,xpos,ypos);


				currently_selected = false;
				//current_player = current_player*-1;
				return false;

		} else if (  xpos == current[0]+1 && ypos == current[1]+(negate*current_player) && !(is_chip(current_player, current[0]+1, current[1]+(negate*current_player)))
					&& !(is_chip(current_player*-1, current[0]+1, current[1]+(negate*current_player))) ) {

						move_chip(current_player, xpos, ypos, current[0], current[1], isKing); //move chip to new location
						remove_chip(current_player, current[0], current[1]); //remove the old chip

						//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
						make_king(current_player,xpos,ypos);


						currently_selected = false;
						//current_player = current_player*-1;
						return false;

		}

	//potentially replace the current[0] with just like xpos in the certain if statements

		//Logic to check if chip is potential diagonal move spot   (The location the chip will hop to)
		if (((xpos == current[0] - 2) || (xpos == current[0] + 2)) && (ypos == (current[1]+(negate*2*current_player)))) { //add a chip check here
			//std::cout << "Current_ypos-1: " << current[1] - 1 << std::endl;
			//check to see if the spot currently has a chip of that type


							//opposite chip color one spot to the diagonal left									//mouse click y pos on the hop spot
			if ( (is_chip(current_player*-1, current[0]-1, current[1]+(negate*current_player)) && xpos == current[0]-2) &&
							!any_chip( current[0]-2, current[1]+(negate*2*current_player)) ) {

				move_chip(current_player, xpos, ypos, current[0], current[1], isKing); //move the chip
				remove_chip(current_player, current[0], current[1]); //remove the old chip
				remove_chip(current_player*-1, current[0]-1, current[1]+(negate*current_player)); //remove opponents chip

				//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
				make_king(current_player,xpos,ypos);


				//store the current board and original current cords in temp variables

				//set current variables to the spot just moved to
				//see if the newly moved chip is now king chip
				
				//see if there are any reguarly double hop moves and if so then take the move and add board to checker array
						//reset variables back to original values
						//AI function will handle adding the original array without the double hop board

				///////////////////////////

				int tempX = current[0];
				int tempY = current[1];
				AI::Board tempBoard = checker_array;

				current[0] = xpos;
				current[1] = ypos;

				bool tempKing = is_king(current_player,current_cords[0], current_cords[1]);

				//Refractor the right diagonal (else) code to be like this for checking double hop
				if ( (select_chip(current_cords[0]-2,current_cords[1]+(2*negate*current_player), current_cords) ||
					select_chip(current_cords[0]+2,current_cords[1]+(2*negate*current_player), current_cords)) ){
					//(Game::select_chip(current_cords[0]+2,current_cords[1]+(2*negate*-1*current_player), current_cords)	||
						//Game::select_chip(current_cords[0]-2,current_cords[1]+(2*negate*-1*current_player), current_cords)) ) {
						//currently_selected = true;
						//render_popup = true;

						move_chip(current_player, xpos, ypos, current[0], current[1], isKing); //move the chip
						remove_chip(current_player, current[0], current[1]); //remove the old chip
						remove_chip(current_player*-1, current[0]-1, current[1]+(negate*current_player)); //remove opponents chip

						//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
						make_king(current_player,xpos,ypos);

						children.push_back(checker_array);
						tempBoard = checker_array;
						current[0] = tempX;
						current[1] = tempY;
						currently_selected = false;
						return false;
					}
					else if (isKing) {

						negate *= -1;
						if ((select_chip(current_cords[0]-2, current_cords[1]+(2*negate*current_player),current_cords) ||
							select_chip(current_cords[0]+2, current_cords[1]+(2*negate*current_player),current_cords))) {
								

								move_chip(current_player, xpos, ypos, current[0], current[1], isKing); //move the chip
								remove_chip(current_player, current[0], current[1]); //remove the old chip
								remove_chip(current_player*-1, current[0]-1, current[1]+(negate*current_player)); //remove opponents chip

								//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
								make_king(current_player,xpos,ypos);

								negate *= -1;
								children.push_back(checker_array);
								tempBoard = checker_array;
								current[0] = tempX;
								current[1] = tempY;
								currently_selected = false;

								return false;
						} 
						negate *= -1;

					}

				tempBoard = checker_array;
				current[0] = tempX;
				current[1] = tempY;
				currently_selected = false;
				return false;

														//opposite chip color one spot to right
			} else if (xpos == current[0]+2 && is_chip(-1*current_player, current[0]+1,current[1]+(negate*current_player)) &&
							!any_chip(current[0]+2, current[1]+(negate*2*current_player)) ) {


						
				move_chip(current_player, xpos, ypos, current[0], current[1], isKing); //move the chip
				remove_chip(current_player, current[0], current[1]); //remove the old chip
				remove_chip(current_player*-1, current[0]+1, current[1]+(negate*current_player)); //remove opponents chip  //#

				//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
				make_king(current_player,xpos,ypos);

				////////////////////////////////

				int tempX = current[0];
				int tempY = current[1];
				AI::Board tempBoard = checker_array;

				current[0] = xpos;
				current[1] = ypos;

				bool tempKing = is_king(current_player,current_cords[0], current_cords[1]);

				if (select_chip(current_cords[0]-2,current_cords[1]+(2*negate*current_player), current_cords) ||
				select_chip(current_cords[0]+2,current_cords[1]+(2*negate*current_player), current_cords))  {
					//currently_selected = true;
					
					move_chip(current_player, xpos, ypos, current[0], current[1], isKing); //move the chip
					remove_chip(current_player, current[0], current[1]); //remove the old chip
					remove_chip(current_player*-1, current[0]-1, current[1]+(negate*current_player)); //remove opponents chip

					//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
					make_king(current_player,xpos,ypos);					
					
					children.push_back(checker_array);
					tempBoard = checker_array;
					current[0] = tempX;
					current[1] = tempY;
					currently_selected = false;
					return false;
					
				}
				else if (isKing) {
					//Try negating the player to try the two other current possibilities
					
					negate *= -1;
					if ((select_chip(current_cords[0]-2, current_cords[1]+(2*negate*current_player),current_cords) ||
					select_chip(current_cords[0]+2, current_cords[1]+(2*negate*current_player),current_cords))) {
							
						move_chip(current_player, xpos, ypos, current[0], current[1], isKing); //move the chip
						remove_chip(current_player, current[0], current[1]); //remove the old chip
						remove_chip(current_player*-1, current[0]-1, current[1]+(negate*current_player)); //remove opponents chip

						//Make king if possible    Pass in the opposite player because current_player was already switched to opposite
						make_king(current_player,xpos,ypos);

						negate *= -1;
						children.push_back(checker_array);
						tempBoard = checker_array;
						current[0] = tempX;
						current[1] = tempY;
						currently_selected = false;
						return false;


					} 
					negate *= -1;
				}
				currently_selected = false;
				return false;	



				///////////////////////////////





			}
		}
	}
    return true;
}

void AI::move_chip(int type, int xpos, int ypos,int old_x, int old_y, bool& isKing) {
	//std::cout << "move chip type: " << checker_array[old_y][old_x] << std::endl;
	if (type == GRID_TYPE_B) {
		if(checker_array.grid[old_y][old_x] == GRID_TYPE_B_KING_TRANS) {
			checker_array.grid[ypos][xpos] = GRID_TYPE_B_KING;
		} else {
			checker_array.grid[ypos][xpos] = GRID_TYPE_B;			
		}

	}

	else if (type == GRID_TYPE_R){

		if(checker_array.grid[old_y][old_x] == GRID_TYPE_R_KING_TRANS) {
			checker_array.grid[ypos][xpos] = GRID_TYPE_R_KING;
		} else {
			checker_array.grid[ypos][xpos] = GRID_TYPE_R;			
		}
		//checker_array[ypos][xpos] = GRID_TYPE_R;
	}
	isKing = false;
}

void AI::remove_chip(int type, int xpos, int ypos) {

	if (type == GRID_TYPE_B) {
		checker_array.grid[ypos][xpos] = GRID_TYPE_NONE;
	}
	else if (type == GRID_TYPE_B_KING) {
		checker_array.grid[ypos][xpos] = GRID_TYPE_NONE;
	}
	else if (type == GRID_TYPE_R) {
		checker_array.grid[ypos][xpos] = GRID_TYPE_NONE;
	}
	else if (type == GRID_TYPE_R_KING) {
		checker_array.grid[ypos][xpos] = GRID_TYPE_NONE;
	}

}

void AI::make_king(int type, int xpos, int ypos) {


	if(type == GRID_TYPE_B && ypos == 0) {
		checker_array.grid[ypos][xpos] = GRID_TYPE_B_KING;
	} else if (type == GRID_TYPE_R && ypos == 7) {
		checker_array.grid[ypos][xpos] = GRID_TYPE_R_KING;
	}


}

void AI::make_trans(int type, int xpos, int ypos) {

	if (type == GRID_TYPE_B) {
		if (checker_array.grid[ypos][xpos] == GRID_TYPE_B_KING) {
			checker_array.grid[ypos][xpos] = GRID_TYPE_B_KING_TRANS;
		} else {
		checker_array.grid[ypos][xpos] = GRID_TYPE_B_TRANS;
		}
	}
	else if (type == GRID_TYPE_R){
			if(checker_array.grid[ypos][xpos] == GRID_TYPE_R_KING) {
				checker_array.grid[ypos][xpos] = GRID_TYPE_R_KING_TRANS;
				
			} else {

				checker_array.grid[ypos][xpos] = GRID_TYPE_R_TRANS;	
			}

	}

}