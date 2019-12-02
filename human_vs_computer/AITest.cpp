
#include "AI.h"

#include <iostream>
#include <vector>


using std::vector;
using std::cout;
using std::endl;


int minimax(AI::Board currentBoard, int depth, bool maximizingPlayer) {
    AI* currPosition;
    if (depth == 0) {
        currPosition = new AI(1,true,-1,currentBoard);
        int score = currPosition->getScore(currPosition->original_board);
        return score; //static evaluation here
    }
    
    if (maximizingPlayer) {
        //set curr player to -1 for reds children
        currPosition = new AI(1,true,-1, currentBoard);
        int maxEval = -1000000;
        int maxPos = -1;
        for(int i=0; i<currPosition->children.size();i++) {
            int eval = minimax(currPosition->children[i], depth-1, false);
            maxEval = std::max(maxEval, eval);
            if (maxEval == eval) {
                maxPos = i;
            }
        }
        cout << "maxpos: " << maxPos << endl;
        currPosition->getBoard(currPosition->children[maxPos]);
        return maxEval;
        
    } else {

        int minEval = 10000000;
        currPosition = new AI(1,false,1,currentBoard); //Set currPlayer to 1 to get Blues children
        
        for(int i=0; i<currPosition->children.size();i++) {
            int eval = minimax(currPosition->children[i], depth-1, true);
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }



}


int main() {




    //Initialize an AI test object because I am lazy and don't feel like copying the init code from AI class over
    //This initializes a board and copys the starting positions over to a 2D array named initial
    
    AI* aiTest = new AI(3,true);
    aiTest->initBoard();
    aiTest->original_board = aiTest->checker_array;


    aiTest->getBoard(aiTest->original_board);
    int result = minimax(aiTest->original_board,3,true);
    aiTest->getChildren();

    /*
    for (int i=0; i<aiTest->children.size(); i++) {
        AI::Board test =  aiTest->children[i];
        //aiTest->getBoard(test);
        cout << aiTest->getScore(test) << endl;
    } */

    cout << "Possible moves: " << aiTest->children.size() << endl;
    cout << "Minimax score is: " << result << endl; 



    










    
   //###################################################



}