#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <strings.h>
#include <math.h>

//--------Const--------

//Game-Size
#define HEIGHT 20
#define WIDTH 20
#define CELL_SIZE 32

#define BOMBE_COUNT 50

//Color
#define COLOR_BOMBE 0x00ff0000
#define COLOR_HIDE 0x00888888
#define COLOR_BG 0x00dddddd
#define COLOR_FLAG 0xff8800
#define COLOR_BORDER 0x00000000

//Input
#define BREAK_CLK 1
#define FLAG_CLK 3


//--------Struct--------

typedef struct s_game
{
	unsigned char **board;
	bool gamover;
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
void render_cell_chance(t_vars *vars, double chance, int x , int y);

//game.c
void init_game(t_game *game);
void break_box(t_vars *vars, int x, int y);
void set_flag(t_vars *vars, int x, int y);
void alloc_game(t_vars *vars);
void check_finish(t_game *game);

//main.c
int mouse_click(int btn, int x, int y, t_vars *vars);

//ia_controler.c
void play_ia(t_vars *vars);
double** get_chance_cell(t_game *game);