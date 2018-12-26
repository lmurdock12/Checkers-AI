#include "SDL.h"


int main(int argc, char*arv[]) {

	//Init SDL subsytems
	SDL_Init(SDL_INIT_EVERYTHING);

	//Create Window
	SDL_Window *window = SDL_CreateWindow("Checkers", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);

	//Create Renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	//Clear and Present
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);

	
	return 0;

}