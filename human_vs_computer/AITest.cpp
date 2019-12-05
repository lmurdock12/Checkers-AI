
#include "AI.h"

#include <iostream>
#include <vector>


using std::vector;
using std::cout;
using std::endl;


int minimax_old(AI::Board currentBoard, int depth, bool maximizingPlayer) {
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
            int eval = minimax_old(currPosition->children[i], depth-1, false);
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
            int eval = minimax_old(currPosition->children[i], depth-1, true);
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }



}

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



int main() {




    //Initialize an AI test object because I am lazy and don't feel like copying the init code from AI class over
    //This initializes a board and copys the starting positions over to a 2D array named initial
    
    #pragma region
    /*
    AI* aiTest1 = new AI(3,true);
    aiTest1->initBoard();
    aiTest1->original_board = aiTest1->checker_array;


    aiTest1->getBoard(aiTest1->original_board);
    int result = minimax_old(aiTest1->original_board,3,true);
    aiTest1->getChildren();

    
    for (int i=0; i<aiTest->children.size(); i++) {
        AI::Board test =  aiTest->children[i];
        //aiTest->getBoard(test);
        cout << aiTest->getScore(test) << endl;
    } 

    cout << "Possible moves: " << aiTest1->children.size() << endl;
    cout << "Minimax score is: " << result << endl; 

    */

    #pragma endregion


    AI* aiTest = new AI(3,true);
    aiTest->initBoard();
    aiTest->original_board = aiTest->checker_array;
    std::cout << "original board: " << std::endl;
    aiTest->getBoard(aiTest->original_board);



    /*
    vector<int> minimax_result = minimax(aiTest->original_board,4,true);
    
    std::cout << minimax_result.size() << std::endl;
    
    int move_index = minimax_result[1];
    int eval = minimax_result[0];
    std::cout << "Evaluation func of: " << eval << std::endl; */

    //Reset AI instance to the original board
    aiTest->checker_array = aiTest->original_board;
    //Set current player to the red player
    aiTest->current_player = -1;
    //get the red players children
    aiTest->getChildren();
    int size = aiTest->children.size();
    
    //std::cout << "possible moves: " << size << std::endl;
    //std::cout << "move index: " << move_index << std::endl;

    //Get the board that was selected as the right move from the move index

    //aiTest->getBoard(aiTest->children[move_index]);
    std::cout << "Possible moves: " << std::endl;
    for (int i=0; i<aiTest->children.size(); i++) {
        AI::Board test =  aiTest->children[i];
        aiTest->getBoard(test);
        cout << "Board score: " << aiTest->getScore(test) << endl;
    } 

    std::cout << "total moves: " << aiTest->children.size() << endl;






    
   //###################################################



}