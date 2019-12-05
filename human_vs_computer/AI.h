#pragma once
#include <vector>

using std::vector;

//struct Board {
	//int grid[8][8];
//};

class AI 
{

public:


	struct Board {
    	int grid[8][8];
	};
	AI::Board checker_array;
	AI::Board original_board;

	int curr_depth;
	bool player;

    void initBoard();
    void getBoard(AI::Board board);

    bool select_chip(int xpos, int ypos, int*& current);
    bool is_chip(int type, int xpos, int ypos);
    bool any_chip( int xpos, int ypos);
    bool is_king(int type, int xpos, int ypos);
    void get_current(int*& current);
    void set_currently_selected(bool val);
    bool validate_move(int xpos, int ypos,int*& current, bool isKing);
    void move_chip(int type, int xpos, int ypos,int old_x, int old_y, bool& isKing);
    void remove_chip(int type, int xpos, int ypos);
    void make_king(int type, int xpos, int ypos);
	void make_trans(int type, int xpos, int ypos);
	bool sequentialHops(int*& current);

	int getScore(AI::Board board);

	AI::Board returnBoard();

    int* getCurrentCordsVar();

	AI(int depth, bool player_turn,int currPlayer, AI::Board check_arr);
	AI();
	AI(int depth, bool player);

	void getChildren();

	vector<AI::Board> children;

	int current_player = GRID_TYPE_B;
	int negate = -1;
private:

	

	enum {
		GRID_TYPE_NONE = 0,
		GRID_TYPE_B=1, //1
		GRID_TYPE_R=-1, //2
		GRID_TYPE_B_TRANS=2, //3
		GRID_TYPE_R_TRANS=3, //4
		GRID_TYPE_B_KING=4,
		GRID_TYPE_R_KING=5,
		GRID_TYPE_B_KING_TRANS=6,
		GRID_TYPE_R_KING_TRANS=7

	
	};


    //int checker_array[8][8];    

	//Current Player;

	bool isKing = false;
	

	//Current Chip //probably will get moved
	bool currently_selected = false;
	int* current_cords = new int[2];


};
