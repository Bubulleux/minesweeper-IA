#include "define/define.h"

int neighbour[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};

void init_game(t_game *game)
{
	game->board = malloc(sizeof(char*) * WIDTH);
	for(int x = 0; x < WIDTH; x++)
	{
		game->board[x] = malloc(sizeof(char) * HEIGHT);
		for(int y = 0; y < HEIGHT; y++)
		{
			game->board[x][y] = 0x10;
		}
	}

	int bombe_count = 0;
	while (bombe_count < BOMBE_COUNT)
	{
		int x = rand() % WIDTH;
		int y = rand() % HEIGHT;
		if (game->board[x][y] == 0x1F)
			continue;
		game->board[x][y] = 0x1F;
		bombe_count += 1;
	}

	for(int x = 0; x < WIDTH; x++)
	{
		for(int y = 0; y < HEIGHT; y++)
		{
			if ((game->board[x][y] & 0x0F) == 0x0F)
				continue;
			

			int neighbour_bombe = 0;
			for(int i = 0; i < 8; i +=1)
			{
				int _x = x + neighbour[i][0];
				int _y = y + neighbour[i][1];
				if (_x != -1 && _x != WIDTH && _y != -1 && _y != HEIGHT && (game->board[_x][_y] & 0x0F) == 0x0F)
				{
					neighbour_bombe += 1;
				}
			}

			game->board[x][y] = (game->board[x][y] & 0xF0) | neighbour_bombe;
		}
	}
}

void break_box(t_vars *vars, int x, int y)
{
	t_game *game = vars->game;
	//printf("Break %d %d\n", x, y);
	if ((game->board[x][y] & 0xF0) != 0x10)
		return;
	
	game->board[x][y] = (game->board[x][y] & 0x0F);

	if ((game->board[x][y] & 0x0F) == 0x00)
	{
		for(int i = 0; i < 8; i +=1)
		{
			int _x = x + neighbour[i][0];
			int _y = y + neighbour[i][1];
			if (_x < 0 || _x >= WIDTH || _y < 0 || _y >= HEIGHT || (game->board[_x][_y] & 0xF0) == 0x00)
			{
				continue;
			}
			break_box(vars, _x, _y);
		}
	}
	render_cell(vars, vars->game->board[x][y], x, y);
	if ((game->board[x][y] & 0x0F) == 0x0F)
	{
		game->gamover = true;
		game->lose += 1;
	}
}



void set_flag(t_vars *vars, int x, int y)
{
	if ((vars->game->board[x][y] & 0xF0) == 0x00)
		return;
	
	char value = (vars->game->board[x][y] & 0xF0) == 0x10 ? 0x20 : 0x10;
	vars->game->board[x][y] = (vars->game->board[x][y] & 0x0F) | value;
	render_cell(vars, vars->game->board[x][y], x, y);
}

void alloc_game(t_vars *vars)
{
	if (vars->game != NULL)
	{
		for(int x = 0; x < WIDTH; x++)
		{
			free(vars->game->board[x]);
		}
		free(vars->game->board);
		
	}
	else
	{
		vars->game = malloc(sizeof(t_game));
	}

	vars->game->gamover = false;
}

void check_finish(t_game *game)
{
	int hide_box_count = 0;
	for(int x = 0; x < WIDTH; x++)
	{
		for(int y = 0; y < HEIGHT; y++)
		{
			if ((game->board[x][y] & 0xF0) != 0x00)
			{
				hide_box_count +=1;
			}
		}
	}
	if (hide_box_count <= BOMBE_COUNT)
	{
		game->gamover = true;
		game->win += 1;
	}
}

bool is_out(int x, int y)
{
	return (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT);
}