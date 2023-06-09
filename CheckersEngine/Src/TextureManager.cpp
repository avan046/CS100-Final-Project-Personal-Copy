#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{

	SDL_Texture* tex = NULL;
	tex = IMG_LoadTexture(Game::renderer, texture);
	if (tex == NULL)
	{
		std::cout << "Image couldnt load file from path: " << texture << "Error: " << IMG_GetError() << std::endl;
	
	}
	return tex;
}

void TextureManager::Draw(SDL_Texture* text, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, text, &src, &dest);
}