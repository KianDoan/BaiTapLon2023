#include"LoadTexture.h"

LoadTexture::LoadTexture()
{}

LoadTexture::~LoadTexture()
{}

SDL_Texture* LoadTexture::loadTex(const char* p_path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* tmpSurface = IMG_Load(p_path);
	if (tmpSurface == NULL)
	{
		cout << "failed to load img" << endl;
	}
	texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return texture;
}
