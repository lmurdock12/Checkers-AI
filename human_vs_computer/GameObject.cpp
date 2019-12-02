#include "GameObject.h"
#include "TextureManager.h"


GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y, int objHeight, int objWidth) {

	renderer = ren; //initialize the renderer to use
	objTexture = TextureManager::LoadTexture(texturesheet, ren); //load the texture to use for the obj using Textmanager class
	xpos = x;
	ypos = y;
	objH = objHeight;
	objW = objWidth;


	srcRect.h = objH;
	srcRect.w = objW;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

}


GameObject::~GameObject()
{
}

void GameObject::Update(int destx, int desty) {

	//If not default argument, then update the position of the object
	if (destx != -1)
		destRect.x = destx;
	if (desty != -1)
		destRect.y = desty;


}

void GameObject::Render() {
	//Render the gameobject to the screen

	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);

}