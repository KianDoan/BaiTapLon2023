#include"Common_Fuction.h"

Common_Fuction::Common_Fuction()
{}

Common_Fuction::~Common_Fuction()
{}

SDL_Texture* Common_Fuction::loadTex(const char* p_path)
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
