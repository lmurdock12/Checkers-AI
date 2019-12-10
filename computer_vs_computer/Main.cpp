// #include "SDL.h" 
#include <SDL2/SDL.h> // for linux
#include "Game.h"
#include <iostream>

Game *game = nullptr;

int main(int argc, char*arv[]) {


	game = new Game();
	game->init("Checkers", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 1600, 0);

	int redWins = 0;
	int blueWins = 0;
	int ties = 0;


	int count = 0;
	int gameCount = 0;
	SDL_Delay(10000);
	while (game->running()) {
		SDL_Delay(1000/10);
		count += 1;

		
		//SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, 0);
		game->handleEvents();
		//game->updateBlue();
		//game->render();
		//SDL_Delay(500);
		//SDL_Delay(200);
		game->current_player = -1;
		game->update(1);
		game->render();
		SDL_Delay(200);
		game->updateBlue();
		game->render();
		//SDL_Delay(200);
		int result = game->check_status();
		if(result != 0) {
			if(result == 1) {
				std::cout << "BLUE WINS..stopping game" <<  std::endl;
				blueWins += 1;
				count = 0;
				gameCount += 1;
				SDL_Delay(300);
				game->initBoard();

			}
			else {
				std::cout << "RED WINS..stopping game" << std::endl;
				count = 0;
				redWins += 1;
				gameCount += 1;
				SDL_Delay(300);
				game->initBoard();

			}
		}


		if(count >= 75) {
			result = game->get_winner();


			
			if(result == 1) {
				std::cout << "BLUE WINS..stopping game" <<  std::endl;
				blueWins += 1;
				count = 0;
				gameCount += 1;
				SDL_Delay(1000);
				game->initBoard();
			}
			else if(result == -1) {
				std::cout << "RED WINS..stopping game" << std::endl;
				count = 0;
				redWins += 1;
				gameCount += 1;
				SDL_Delay(300);
				game->initBoard();
			}
			else {
				std::cout << "TIE GAME..stopping game" << std::endl;
				count = 0;
				ties += 1;
				gameCount += 1;
				SDL_Delay(300);
				game->initBoard();
			}
			

		}


		if(gameCount==25) {
			break;
		}

	}

	std::cout << "Red wins: " << redWins << std::endl;
	std::cout << "Blue wins: " << blueWins << std::endl;
	std::cout << "Ties: " << ties << std::endl;

	//game->getFinalBoard();
	game->clean();
	return 0;

} 