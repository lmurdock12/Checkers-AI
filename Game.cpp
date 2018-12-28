
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "CheckerManager.h"
#include <iostream>
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

GameObject* board;
CheckerManager* chip_manager;


SDL_Rect srcRect, destRect;
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	int flags = 0;//init the unit32 flag
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN; //if fullscreen is true set the flag to fullscreen
	}
	//Checks to see is SDL library is initialized successfully and prints statement

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) { //If Init() == 0; that means success.
		std::cout << "Subsystems Initialized!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) { //if window is true then it has been successfully created
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 244, 244, 24);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true; //if init works successfully then continue to run
	}
	else {
		isRunning = false; //stop the game if it does not initialize 
	}

	currently_selected = false;
	board = new GameObject("assets/checker_board.png", renderer, 0, 0, 800, 800);
	chip_manager = new CheckerManager("assets/checker.png", "assets/red_checker.png",renderer, 100, 100, GRID_TYPE_B);
	current_player = GRID_TYPE_B;
}

void Game::handleEvents() {

	while (SDL_PollEvent(&event)) { //get the event

		switch (event.type) {
		case SDL_QUIT://if the X is pressed then end the game
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			int x, y;
			//SDL_MouseButtonEvent b = event.button;
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&x, &y);
				int x_cord = x/100;
				int y_cord = y/100;
				std::cout << "X is: " << x_cord << std::endl;
				std::cout << "Y is: " << y_cord << std::endl;
				std::cout << "Current player is: " << current_player << std::endl;
				//std::cout << "Currently Selected: " << currently_selected << std::endl;

				if (current_player == GRID_TYPE_B) {
					Game::validate_move(x_cord, y_cord);
				}
				else {
					Game::validate_move(x_cord, y_cord);
				}
			}

		default:
			break;
		}
	}
}


void Game::update() {
	//board->Update();

}


void Game::render() {

	SDL_RenderClear(renderer); //clear the renderer

	board->Render();
	chip_manager->render();
	

	//board->Render();
	SDL_RenderPresent(renderer); //render all the objects

}

void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;

}


void Game::validate_move(int xpos, int ypos) {

	//if player selected a valid chip, get the coords and set currently_selected to true
	if (chip_manager->is_chip(current_player, xpos, ypos) && currently_selected == false) {

		//::ADD:: func to see if chip is movable

		currently_selected = true;
		current_xpos = xpos;
		current_ypos = ypos;
		std::cout << "Current xpos: " << current_xpos << std::endl;
		std::cout << "Current ypos: " << current_ypos << std::endl;
		//update the textures
	}

	//Determine if the new spot is a valid move
	if (currently_selected && (current_player == GRID_TYPE_B)) {

		//check if the chip is proper diagonal move
		if (((xpos == current_xpos - 1) || (xpos == current_xpos + 1)) && (ypos == (current_ypos - 1))) {
			std::cout << "Current_ypos-1: " << current_ypos - 1 << std::endl;
			//check to see if the spot currently has a chip of that type
			if (!(chip_manager->is_chip(current_player, xpos, ypos))) {

				chip_manager->move_chip(current_player, xpos, ypos); //move the chip
				chip_manager->remove_chip(current_player, current_xpos, current_ypos); //remove the old chip
				currently_selected = false;
				current_player = GRID_TYPE_R; //switch players
			}
		}

	} else if (currently_selected && (current_player == GRID_TYPE_R))

		//check if chip proper diagonal move
		if (((xpos == current_xpos + 1) || (xpos == current_xpos - 1)) && (ypos == current_ypos + 1)) {

			//check to see if the spot currently has a chip of that type
			if (!(chip_manager->is_chip(current_player, xpos, ypos))) {

				chip_manager->move_chip(current_player, xpos, ypos); //move the chip
				chip_manager->remove_chip(current_player, current_xpos, current_ypos); //remove the old chip
				currently_selected = false; 
				current_player = GRID_TYPE_B; //switch player
			}
		}
}