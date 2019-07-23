#pragma once
#include <vector>

using std::vector;

struct Board {
	int grid[8][8];
};

class AI 
{

public:


	//struct Board {
    	//int grid[8][8];
	//};
    void initBoard();
    void getBoard(vector<Board>& boards);
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

    int* getCurrentCordsVar();

	Board checker_array;

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
	int current_player = GRID_TYPE_B;
	int direction;
	bool isKing = false;
	int negate = -1;
	int jump_again = false;
	//int render_popup = false;
	bool pop_status = false;
	int* temp_cords;
	int tempx;
	int tempy;
	//Current Chip //probably will get moved
	bool currently_selected = false;
	int* current_cords;


};
