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
				printf("%d   %d \n", _x, _y);
				if (_x != -1 && _x != WIDTH && _y != -1 && _y != HEIGHT && (game->board[_x][_y] & 0x0F) == 0x0F)
				{
					printf("ADD neighbour bombe");
					neighbour_bombe += 1;
				}
			}

			game->board[x][y] = (game->board[x][y] & 0xF0) | neighbour_bombe;
			printf("%d, %d: %d   %X   \n", x, y, neighbour_bombe, game->board[x][y]);
		}
	}
}