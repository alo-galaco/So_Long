#include "so_long.h"

int main ()
{
	t_mlx window;

	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, WIDTH, HEIGHT, "So_long");
	mlx_loop(window.mlx);
}