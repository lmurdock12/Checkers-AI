
#include "AI.h"
#include "Game.h"
#include <iostream>
#include <vector>
AI *aiTest = nullptr;

using std::vector;

class Node {

public:
	struct Board {
    	int grid[8][8];
	};
    Node(int depth, int player, Board check_arr);
private:

	Board checker_array;

    int curr_depth;
    int player;
    vector<Node> children;



};

 Node::Node(int depth, int player, Board check_arr) {

     curr_depth = depth;
     player = player;
     //checker_array = checker_array;

}

int main() {


    Node::Board test;
    test.grid[0][0] = 1;

    Node *x = nullptr;
    x = new Node(5,5, test);



    
    /* 
   //###################################################

    //std::cout << "Main file test" << std::endl;
    aiTest = new AI(); //Create AI instance

    vector<AI::Board> boards;

    aiTest->initBoard();
    //aiTest->getBoard(boards);

    int* current;
    //aiTest->get_current(current);

    std::cout << "Original board: " << std::endl;
    aiTest->getBoard();

    for(int i=0; i<8; i++) {
            std::cout << "next row" << std::endl;
        for(int j=0; j<8; j++) {
            std::cout << "next column" << std::endl;
            aiTest->set_currently_selected(false);
            current = aiTest->getCurrentCordsVar(); //Get the current value of 
            bool foundMove = false;

            //aiTest->getBoard();
            aiTest->initBoard();
            //aiTest->getBoard();
            //See if current cords is a selectable chip
            if(aiTest->select_chip(j,i,current)) {
                std::cout << "got selection" << std::endl;
                //Get the current cords of selected chip
                //current = aiTest->getCurrentCordsVar();
                //if valid move was made print the updated board
                if(!aiTest->validate_move(current[0]-1,current[1]-1,current,false)) {

                    std::cout << "got move" << std::endl;
                    aiTest->addBoard(boards);
                    aiTest->getBoard();
                    aiTest->initBoard();
                    aiTest->set_currently_selected(true);
                    foundMove = true;

                }
                //std::cout << "current board is: " <<std::endl;
                //aiTest->getBoard(boards);
                if (!aiTest->validate_move(current[0]+1,current[1]-1,current,false)) {
                    std::cout << "got move" << std::endl;
                    aiTest->addBoard(boards);
                    aiTest->getBoard();
                    aiTest->initBoard();
                    aiTest->set_currently_selected(true);
                    foundMove = true;

                } 
                if(!aiTest->validate_move(current[0]-2,current[1]-2,current,false)) {

                    std::cout << "got move" << std::endl;
                    aiTest->addBoard(boards);
                    aiTest->getBoard();
                    aiTest->initBoard();
                    aiTest->set_currently_selected(true);
                    foundMove = true;

                }
                if(!aiTest->validate_move(current[0]+2,current[1]-2,current,false)) {
                    std::cout << "got move" << std::endl;
                    aiTest->addBoard(boards);
                    aiTest->getBoard();
                    aiTest->initBoard();
                    aiTest->set_currently_selected(true);
                    foundMove = true;


                }
                if (foundMove == true) {
                    std::cout << "did not find move" << std::endl;
                }
                aiTest->set_currently_selected(false);

            }

            //If a chip was selected check the following to see if a valid move.
                //simple left, right
                //hop left, right

            //loop through new boards and see if that board is in the list
            //if not in the list then add the board to the list.

            
            
        }

    }

    std::cout << "size of boards:" << boards.size() << std::endl;
    */


}