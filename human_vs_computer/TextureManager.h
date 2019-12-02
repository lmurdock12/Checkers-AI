#pragma once
#include "Game.h"


class TextureManager
{
public:
	//Static calls it as a clase function instead of member function (dont have to create object)
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
	TextureManager();
	~TextureManager();
};

