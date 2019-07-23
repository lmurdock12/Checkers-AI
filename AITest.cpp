
#include "AI.h"
#include "Game.h"
#include <iostream>
#include <vector>
AI *aiTest = nullptr;

using std::vector;

struct test {

    int board[8][8];

};


int main() {

    /* 
    test joe;
    joe.board[0][0] = 1;
    test alex; 
    alex.board[0][0] = 2;

    vector<test> boards;
    boards.push_back(joe);
    boards.push_back(alex);

    for (int i=0; i<boards.size();i++) {
        
        std::cout << boards[i].board[0][0] <<  std::endl;

    }
    std::cout << joe.board[0][0] << std::endl;
    */

    
    


    std::cout << "Main file test" << std::endl;
    aiTest = new AI(); //Create AI instance

    vector<Board> boards;

    aiTest->initBoard();
    //aiTest->getBoard(boards);

    int* current;
    //aiTest->get_current(current);

    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {

            aiTest->set_currently_selected(false);
            current = aiTest->getCurrentCordsVar(); //Get the current value of 

            //See if current cords is a selectable chip
            if(aiTest->select_chip(j,i,current)) {
                
                //Get the current cords of selected chip
                current = aiTest->getCurrentCordsVar();
                //if valid move was made print the updated board
                if(!aiTest->validate_move(current[0]-1,current[1]-1,current,false)) {

                        std::cout << "SUCCESSFULL BOARD MOVE" << std::endl;
                        aiTest->getBoard(boards);

                        
                        aiTest->initBoard();
                } else {
                    std::cout << "did not find move" << std::endl;
                }

            }

            //If a chip was selected check the following to see if a valid move.
                //simple left, right
                //hop left, right

            //loop through new boards and see if that board is in the list
            //if not in the list then add the board to the list.

            
            
        }

    }

    std::cout << "size of boards:" << boards.size() << std::endl;
    


}