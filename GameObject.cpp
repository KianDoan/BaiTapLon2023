#include"GameObject.h"

GameObject::GameObject(const char* p_path, int p_x, int p_y)
{
	status = RIGHT_FALL;
	objTexture = Common_Fuction::loadTex(p_path);
	x_pos = p_x;
	y_pos = p_y;
	object_scroll = 0;
	map_scroll = 0;
	right = 0;
	left = 0;
	jump = 0;
	frame = 0;
	gravity_speed = 0;
	on_ground = false;
	is_dead = false;
	lever = 0;
}

GameObject::~GameObject()
{}

void GameObject::update(Map& map_data)
{
	velocity = 0;
	gravity_speed += 1.5;

	if (right == 1)
		velocity += 12;

	if (left == 1)
		velocity -= 12;

	CheckToMap(map_data);
	scrollMap(map_data);

	if (jump == 1 && on_ground == true)
	{
		gravity_speed -= 18;
		on_ground = false;
		jump = 0;
	}

	if (!on_ground)
	{
		switch (status)
		{
		case MOVE_RIGHT:
			objTexture = Common_Fuction::loadTex("Resources/gfx/right_fall.png");
			break;
		case MOVE_LEFT:
			objTexture = Common_Fuction::loadTex("Resources/gfx/left_fall.png");
			break;
		case STAND_RIGHT:
			objTexture = Common_Fuction::loadTex("Resources/gfx/right_fall.png");
			break;
		case STAND_LEFT:
			objTexture = Common_Fuction::loadTex("Resources/gfx/left_fall.png");
			break;
		default:
			break;
		}
	}
	else
	{
		if (status == STAND_LEFT)
			objTexture = Common_Fuction::loadTex("Resources/gfx/left_stand.png");
		if (status == STAND_RIGHT)
			objTexture = Common_Fuction::loadTex("Resources/gfx/right_stand.png");
		if(status == MOVE_RIGHT)
			objTexture = Common_Fuction::loadTex("Resources/gfx/move_right.png");
		if(status == MOVE_LEFT)
			objTexture = Common_Fuction::loadTex("Resources/gfx/move_left.png");
	}

	x_pos += velocity;
	y_pos += gravity_speed;

	destRect.x = x_pos - object_scroll;
	destRect.y = y_pos;
	destRect.w = 64;
	destRect.h = 64;

	if (destRect.y >= 600)
		is_dead = true;
	if (destRect.x <= 0)
		is_dead = true;
}

void GameObject::render()
{
	SDL_RenderCopy(Game::renderer, objTexture, NULL, &destRect);
}

void GameObject::loadClips()
{
	for (int i = 0; i < 6; i++)
	{
		frame_clip[i].x = i * 32;
		frame_clip[i].y = 0;
		frame_clip[i].w = 32;
		frame_clip[i].h = 32;
	}
}

void GameObject::renderClip()
{
	frame++;
	if (frame > 5)
		frame = 0;
	SDL_Rect* curr_clip = &frame_clip[frame];

	SDL_RenderCopy(Game::renderer, objTexture, curr_clip, &destRect);

}

bool GameObject::handlePlayerInput()
{
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT || is_dead == true)
	{
		return true;
	}
	else
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_RIGHT:
				status = MOVE_RIGHT;
				right = 1;
				left = 0;
				cout << "right" << endl;
				break;
			case SDLK_LEFT:
				status = MOVE_LEFT;
				right = 0;
				left = 1;
				cout << "left" << endl;
				break;
			case SDLK_UP:
				jump = 1;
				cout << "up" << endl;
				break;
			default:
				break;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_RIGHT:
				status = STAND_RIGHT;
				right = 0;
				break;
			case SDLK_LEFT:
				status = STAND_LEFT;
				left = 0;
				break;
			case SDLK_UP:
				jump = 0;
				break;
			}
		}
		return false;
	}
}

void GameObject::CheckToMap(Map& map_data)
{
	int x1, x2, y1, y2;

	x1 = (x_pos + velocity + map_scroll + 1) / 64;
	x2 = (x_pos + velocity + 40 - 1 + map_scroll) / 64;
	y1 = (y_pos) / 64;
	y2 = (y_pos + 64 - 1) / 64;

	if (velocity > 0)
	{
		if (map_data.gameMap[y1][x2] != 0 || map_data.gameMap[y2][x2] != 0)
		{
			x_pos = (x2) * 64 + 24 - map_scroll;
			x_pos -= (64 + 1);
			velocity = 0;
		}
	}
	else if (velocity < 0)
	{
		if (map_data.gameMap[y1][x1] != 0 || map_data.gameMap[y2][x1] != 0)
		{
			x_pos = (x1+ 1) * 64 - map_scroll;
			velocity = 0;
		}
	}

	x1 = (x_pos + map_scroll + 1) / 64;
	x2 = (x_pos + 40 - 1 + map_scroll) / 64;
	y1 = (y_pos - 16 + gravity_speed) / 64;
	y2 = (y_pos + gravity_speed + 64 - 1) / 64;

	if (gravity_speed > 0)
	{
		if (map_data.gameMap[y2][x1] != 0 || map_data.gameMap[y2][x2] != 0)
		{
			y_pos = y2 * 64 - 64 - 1;
			gravity_speed = 0;
			on_ground = true;
		}
	}
	else if (gravity_speed < 0)
	{
		if (map_data.gameMap[y1][x1] != 0 || map_data.gameMap[y1][x2] != 0)
		{
			y_pos = (y1 + 1) * 64;
			gravity_speed = 0;
		}
	}
}

void GameObject::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	int left_a = object1.x + 2;
	int right_a = object1.x + 38;
	int top_a = object1.y + 18;
	int bottom_a = object1.y + 62;

	int left_b = object2.x + 2;
	int right_b = object2.x + 62;
	int top_b = object2.y + 2;
	int bottom_b = object2.y + 62;

	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			is_dead = true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			is_dead = true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			is_dead = true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			is_dead = true;
		}
	}
}

void GameObject::scrollMap(Map& map_data)
{
	object_scroll += 5;

	if (map_data.map_start == 0)
	{		
		map_scroll -= 1280;
	}
}

//ThreatObject

ThreatObject::ThreatObject(int p_x, int p_y, int p_seed)
{
	seed = p_seed;

	x_val = -10;
	y_val = 13;
	object_scroll = 0;
	map_scroll = 0;
	
	dest_rect.x = p_x;
	dest_rect.y = p_y;
	dest_rect.w = 64;
	dest_rect.h = 64;

	threat_texture = Common_Fuction::loadTex("Resources/gfx/threat.png");
}

ThreatObject::~ThreatObject()
{}

void ThreatObject::Update(Map& map_data)
{
	if (seed == 0)
	{
		seed = time(NULL);
	}

	srand(seed);

	if (map_data.map_start == 0)
	{
		map_scroll -= 1280;
	}

	dest_rect.x += x_val;
	dest_rect.y += y_val;

	if (dest_rect.y >= 640 || !Accident(map_data))
	{
		dest_rect.x = rand() % 981 + 300;
		dest_rect.y = -100;
		seed = rand();
	}
}

void ThreatObject::Render()
{
	SDL_RenderCopy(Game::renderer, threat_texture, NULL, &dest_rect);
}

bool ThreatObject::Accident(Map& map_data)
{
	int x1, x2, y1, y2;

	x1 = (dest_rect.x+ 1) / 64;
	x2 = (dest_rect.x + 64 - 1) / 64;
	y1 = (dest_rect.y) / 64;
	y2 = (dest_rect.y + 64 - 1) / 64;

	if (map_data.gameMap[y1][x1] != 0 || map_data.gameMap[y2][x1] != 0 || map_data.gameMap[y1][x2] != 0 || map_data.gameMap[y2][x2] != 0)
	{
		return false;
	}
	return true;
}