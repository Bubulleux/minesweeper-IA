#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <strings.h>

//--------Const--------

//Game-Size
#define HEIGHT 20
#define WIDTH 20
#define CELL_SIZE 32

#define BOMBE_COUNT 50

//Color
#define COLOR_BOMBE 0x00ff0000
#define COLOR_HIDE 0x00bbbbbb
#define COLOR_BORDER 0x00000000


//--------Struct--------

typedef struct s_game
{
	unsigned char **board;
} t_game;

typedef struct s_vars
{
	void *mlx;
	void *window;

	t_game *game;
	
} t_vars;


typedef struct s_img
{
	void *img;
	char *addr;
	int bit_per_pixel;
	int line_lenght;
	int endian;
} t_img;



//--------Function--------

//renderer.c
void render(t_vars *vars);
void render_all_game(t_vars *vars);
void render_cell(t_vars *vars, char value, int x, int y);
void set_pixel(t_img *img, int x, int y, int color);

//game.c
void init_game(t_game *game);