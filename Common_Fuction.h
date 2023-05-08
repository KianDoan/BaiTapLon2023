#ifndef LOAD_TEXTURE_H_
#define LOAD_TEXTURE_H_

#include"Game.h"

class Common_Fuction
{
public:
	Common_Fuction();
	~Common_Fuction();
	static SDL_Texture* loadTex(const char* p_path);
private:

};

#endif // !LOAD_TEXTURE_H_
