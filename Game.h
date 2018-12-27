#include "SDL.h"



class Game {

public: 


	//Initialize game
	void init(const char* title, int xpos, int ypos, int width, int height,bool fullscreen);

	//HandleEvents();
	void handleEvents();

	//Update events
	void update();

	//Render game
	void render();

	void clean();

	bool running() { return isRunning; }

private:
	
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;




};




