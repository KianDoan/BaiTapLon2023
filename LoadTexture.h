#ifndef LOAD_TEXTURE_H_
#define LOAD_TEXTURE_H_

#include"Game.h"

class LoadTexture
{
public:
	LoadTexture();
	~LoadTexture();
	static SDL_Texture* loadTex(const char* p_path);
private:

};

#endif // !LOAD_TEXTURE_H_
