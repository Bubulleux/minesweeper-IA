#include "define/define.h"

int main()
{
	t_vars *vars = malloc(sizeof(t_vars));
	
	vars->mlx = mlx_init();
	vars->window = mlx_new_window(vars->mlx, WIDTH * CELL_SIZE + 10, HEIGHT * CELL_SIZE + 40, "Minesweeper");
	srand(time(NULL));

	vars->game = malloc(sizeof(t_game));

	char c = 0xc8;
	printf("%X %X\n", c, (c & 0xf0) | 4);


	init_game(vars->game);
	render(vars);

	mlx_loop(vars->mlx);
	return 0;
}