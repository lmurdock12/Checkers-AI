
#include "Game.h"
#include <iostream>


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
}

void Game::handleEvents() {

	SDL_PollEvent(&event);

	switch (event.type) {

		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;

	}
}

void Game::update() {


}

void Game::render() {

	SDL_RenderClear(renderer); //clear the renderer

	SDL_RenderPresent(renderer); //render all the objects

}

void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;

}