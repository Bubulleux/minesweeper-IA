#include "define/define.h"

void render(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->window);
	render_all_game(vars);
}

void render_all_game(t_vars *vars)
{

	for(int x = 0; x < WIDTH; x++)
	{
		for(int y = 0; y < HEIGHT; y++)
		{
			char value = vars->game->board[x][y];
			render_cell(vars, value, x, y);
		}
	}
	
	
}

void render_cell(t_vars *vars, char value, int x , int y)
{
	t_img *img = malloc(sizeof(t_img));
	img->img = mlx_new_image(vars->mlx, CELL_SIZE, CELL_SIZE);
	img->addr = mlx_get_data_addr(img->img, &img->bit_per_pixel, &img->line_lenght, &img->endian);

	int color = 0x000000;
	if ((value & 0xF0) == 0x10)
		color = COLOR_HIDE;
	else if ((value & 0xF0) == 0x20)
	{
		color = COLOR_FLAG;
	}
	else if ((value & 0xF0) == 0x00 && (value & 0x0F) != 0x0F)
	{
		color = COLOR_BG;
	}
	else
	{
		color = COLOR_BOMBE;
	}


	for(int _x = 0; _x < CELL_SIZE; _x++)
	{
		for(int _y = 0; _y < CELL_SIZE; _y++)
		{
			if (_x == 0 || _x == CELL_SIZE - 1 || _y == 0 || _y == CELL_SIZE - 1)
				set_pixel(img, _x, _y, COLOR_BORDER);
			else
			{
				set_pixel(img,_x, _y, color);
			}
		}
	}

	mlx_put_image_to_window(vars->mlx, vars->window, img->img, x * CELL_SIZE + 5, y * CELL_SIZE + 35);
	mlx_destroy_image(vars->mlx, img->img);
	free(img);

	if ((value & 0x0F) != 0x0F && (value & 0x0F) != 0x00 && (value & 0xF0) == 0x00)
	{
		char num[30];
		sprintf(num, "%d", (value & 0x0F));
		mlx_string_put(vars->mlx, vars->window, x * CELL_SIZE + 19, y * CELL_SIZE + 55, 0x00111111, num);
	}
}

void set_pixel(t_img *img, int x, int y, int color)
{
	char **dst;
	dst = (char**) malloc(sizeof(char*));
	*dst = img->addr + (y * img->line_lenght + x * (img->bit_per_pixel / 8));
	*(unsigned int*)*dst = color;
	free(dst);
}