#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* ren) {

	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* text = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);
	return text;

}

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}
