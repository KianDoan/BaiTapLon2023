#include"GameObject.h"

GameObject::GameObject(const char* p_path, int p_x, int p_y)
{
	status = RIGHT_FALL;
	objTexture = LoadTexture::loadTex(p_path);
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

	accident(map_data);
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
			objTexture = LoadTexture::loadTex("Resources/gfx/right_fall.png");
			break;
		case MOVE_LEFT:
			objTexture = LoadTexture::loadTex("Resources/gfx/left_fall.png");
			break;
		case STAND_RIGHT:
			objTexture = LoadTexture::loadTex("Resources/gfx/right_fall.png");
			break;
		case STAND_LEFT:
			objTexture = LoadTexture::loadTex("Resources/gfx/left_fall.png");
			break;
		default:
			break;
		}
	}
	else
	{
		if (status == STAND_LEFT)
			objTexture = LoadTexture::loadTex("Resources/gfx/left_stand.png");
		if (status == STAND_RIGHT)
			objTexture = LoadTexture::loadTex("Resources/gfx/right_stand.png");
		if(status == MOVE_RIGHT)
			objTexture = LoadTexture::loadTex("Resources/gfx/move_right.png");
		if(status == MOVE_LEFT)
			objTexture = LoadTexture::loadTex("Resources/gfx/move_left.png");
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

void GameObject::accident(Map& map_data)
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
	y1 = (y_pos + gravity_speed) / 64;
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

void GameObject::scrollMap(Map& map_data)
{
	object_scroll += 5;

	if (map_data.map_start == 0)
	{		
		map_scroll -= 1280;
	}
}