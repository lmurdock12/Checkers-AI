// #include "SDL.h" 
#include <SDL2/SDL.h> // for linux
#include "Game.h"

Game *game = nullptr;

int main(int argc, char*arv[]) {
	game = new Game();
	game->init("Checkers", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 1600, 0);
	while (game->running()) {
		//SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, 0);
		//game->handleEvents();
		game->updateBlue();
		game->render();
		SDL_Delay(200);
		game->update();
		game->render();
		SDL_Delay(200);
	}

	game->clean();
	return 0;

}