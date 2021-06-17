#include "define/define.h"

int neighbour_ia[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};

void play_ia(t_vars *vars)
{
	t_game *game = vars->game; 
	double **board_of_chance = get_chance_cell(game);
	double min = 8;
	int count_of_min = 0;
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			if ((game->board[x][y] & 0xF0) == 0x00)
			{
				continue;
			}

			render_cell_chance(vars,  board_of_chance[x][y], x, y);
			if (board_of_chance[x][y] < min)
			{
				min = board_of_chance[x][y];
				count_of_min = 0;
			}
			if (board_of_chance[x][y] == min)
			{
				count_of_min += 1;
			}
		}
	}

	int index = rand() % count_of_min;
	bool break_loop = false;
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			if ((game->board[x][y] & 0xF0) == 0x00)
			{
				continue;
			}
			if (board_of_chance[x][y] == min)
			{
				if (index > 0 )
				{
					index -= 1;
				}
				else
				{
					printf("value: %f\n", min);
					break_box(vars, x, y);
					break_loop = true;
					break;
				}
			}
		}
		if (break_loop)
		{
			break;
		}
	}
	for (int i = 0; i < WIDTH; i++)
	{
		free(board_of_chance[i]);
	}
	free(board_of_chance);
}

double** get_chance_cell(t_game *game)
{
	double **board_of_chance = malloc(sizeof(double*) * WIDTH);
	for (int i = 0; i < WIDTH; i++)
	{
		board_of_chance[i] = malloc(sizeof(double) * HEIGHT);
	}

	unsigned char **board_count = malloc(sizeof(unsigned char*) * WIDTH);
	for (int i = 0; i < WIDTH; i++)
	{
		board_count[i] = malloc(sizeof(unsigned char) * HEIGHT);
	}
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			board_of_chance[x][y] = -1;
			board_count[x][y] = 0;
		}
	}
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			if ((game->board[x][y] & 0xF0) != 0x00 || (game->board[x][y] & 0x0F) == 0x00 || (game->board[x][y] & 0x0F) == 0x0F)
			{
				continue;
			}		

			int neighbour_count = 0;
			for (int i = 0; i < 8; i++)
			{
				int n_x = x + neighbour_ia[i][0], n_y = y + neighbour_ia[i][1];
				if (is_out(n_x, n_y))
				{
					continue;
				}

				if ((game->board[n_x][n_y] & 0xF0) != 0x00)
				{
					neighbour_count += 1;
				}
			}
			if (neighbour_count <= (game->board[x][y] & 0x0F))
			{
				for (int i = 0; i < 8; i++)
				{
					int n_x = x + neighbour_ia[i][0], n_y = y + neighbour_ia[i][1];
					if (is_out(n_x, n_y))
					{
						continue;
					}

					if ((game->board[n_x][n_y] & 0xF0) != 0x00)
					{
						board_of_chance[n_x][n_y] = 1;
					}
				}
			}
		}
	}

	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			if ((game->board[x][y] & 0xF0) != 0x00 || (game->board[x][y] & 0x0F) == 0x00 || (game->board[x][y] & 0x0F) == 0x0F)
			{
				continue;
			}
			

			int neighbour_count_bombe = 0;
			for (int i = 0; i < 8; i++)
			{
				int n_x = x + neighbour_ia[i][0], n_y = y + neighbour_ia[i][1];
				if (is_out(n_x, n_y))
				{
					continue;
				}

				if ((game->board[n_x][n_y] & 0xF0) != 0x00 && board_of_chance[n_x][n_y] == 1)
				{
					neighbour_count_bombe += 1;
				}
			}
			if (neighbour_count_bombe >= (game->board[x][y] & 0x0F))
			{
				for (int i = 0; i < 8; i++)
				{
					int n_x = x + neighbour_ia[i][0], n_y = y + neighbour_ia[i][1];
					if (is_out(n_x, n_y))
					{
						continue;
					}
					if ((game->board[n_x][n_y] & 0xF0) != 0x00 && board_of_chance[n_x][n_y] == -1)
					{
						board_of_chance[n_x][n_y] = 0;
					}
				}
			}
		}
	}

	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			if ((game->board[x][y] & 0xF0) != 0x00 || (game->board[x][y] & 0x0F) == 0x00 || (game->board[x][y] & 0x0F) == 0x0F)
			{
				continue;
			}
			

			int neighbour_bombe = 0;
			int neighbour_voide = 0;
			int neighbour_count = 0;
			for (int i = 0; i < 8; i++)
			{
				int n_x = x + neighbour_ia[i][0], n_y = y + neighbour_ia[i][1];
				if (is_out(n_x, n_y))
				{
					continue;
				}

				if ((game->board[n_x][n_y] & 0xF0) != 0)
				{
					neighbour_count += 1;
					if (board_of_chance[n_x][n_y] == 1)
					{
						neighbour_bombe += 1;
					}
					if (board_of_chance[n_x][n_y] == 0)
					{
						neighbour_voide += 1;
					}
				}
			}
			if (neighbour_bombe < (game->board[x][y] & 0x0F))
			{
				double luck = ((game->board[x][y] & 0x0F) - neighbour_bombe) / (double)(neighbour_count - neighbour_bombe - neighbour_voide);
				for (int i = 0; i < 8; i++)
				{
					int n_x = x + neighbour_ia[i][0], n_y = y + neighbour_ia[i][1];
					if (is_out(n_x, n_y))
					{
						continue;
					}
					if ((game->board[n_x][n_y] & 0xF0) != 0x00 && board_of_chance[n_x][n_y] != 0 && board_of_chance[n_x][n_y] != 1)
					{
						if (board_of_chance[n_x][n_y] == -1)
						{
							board_of_chance[n_x][n_y] = 0;
						}
						board_of_chance[n_x][n_y] += luck;
						board_count[n_y][n_y] +=1 ;
					}
				}
			}
		}
	}

	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			if (board_of_chance[x][y] == -1)
			{
				board_of_chance[x][y] = 0.9;
			}
			if (board_count[x][y] != 0)
			{
				board_of_chance[x][y] = board_of_chance[x][y] / (double)board_count[x][y];
			}
		}
	}

	for (int i = 0; i < WIDTH; i++)
	{
		free(board_count[i]);
	}
	free(board_count);

	return board_of_chance;
}

