#include "define/define.h"


int mouse_click(int btn, int x, int y, t_vars *vars)
{
	if (vars->game->gamover || btn == 2)
	{
		alloc_game(vars);
		init_game(vars->game);
		render(vars);
		return 1;
	}
	if (x >= 5 && x < WIDTH * CELL_SIZE + 5 && y >= 35 && y < HEIGHT * CELL_SIZE + 35)
	{
		if (btn == BREAK_CLK)
			break_box(vars, (x - 5) / CELL_SIZE, (y - 35) / CELL_SIZE);
		else if (btn == FLAG_CLK)
			set_flag(vars, (x - 5) / CELL_SIZE, (y - 35) / CELL_SIZE);
		check_finish(vars->game);
	}
	return 1;
}



int main()
{
	t_vars *vars = malloc(sizeof(t_vars));
	
	vars->mlx = mlx_init();
	vars->window = mlx_new_window(vars->mlx, WIDTH * CELL_SIZE + 10, HEIGHT * CELL_SIZE + 40, "Minesweeper");
	srand(time(NULL));

	vars->game = NULL;

	char c = 0xc8;
	printf("%X %X\n", c, (c & 0xf0) | 4);

	alloc_game(vars);

	init_game(vars->game);
	render(vars);

	mlx_mouse_hook(vars->window, &mouse_click, vars);

	mlx_loop(vars->mlx);
	return 0;
}