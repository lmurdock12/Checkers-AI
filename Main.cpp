// #include "SDL.h" 
#include <SDL2/SDL.h> // for linux
#include "Game.h"

Game *game = nullptr;

int main(int argc, char*arv[]) {

	game = new Game();
	game->init("Checkers", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);
	while (game->running()) {

		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();
	return 0;

}