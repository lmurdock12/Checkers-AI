#pragma once
#include "Game.h"
class GameObject
{
public:


	GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y, int objHeight, int objWidth);
	~GameObject();

	void Update(int destx = -1, int desty = -1); //Initialize the update position with default arguments in case no change wants to be made
	void Render();


private:
	//Data keeping track of the object
	int xpos;
	int ypos;
	int objH;
	int objW;

	//Texture of the object
	SDL_Texture* objTexture;
	//Where to place the object
	SDL_Rect srcRect, destRect;
	//Renderer to use
	SDL_Renderer* renderer;
};

