#include "../includes/so_long.h"
#include <X11/keysym.h>

#define MLX_ERROR 1
#define RED_COLOR 0xFF0000
#define GREEN_COLOR 0xFF00

typedef struct s_rectangle
{
	int x;
	int y;
	int r_width;
	int r_height;
	int color;
}				t_rectangle;

int key_close(int keysym, t_mlx *data)
{
	if (keysym == XK_Escape)
	{	
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	printf("Keypress: %d\n", keysym);
	return (0);
}

int	render_rectangle(t_mlx *data, t_rectangle rectangle)
{
	int i;
	int j;

	if (data->win == NULL)
		return (MLX_ERROR);
	i = rectangle.y;
	while (i < rectangle.y + rectangle.r_height)
	{
		j = rectangle.x;
		while (j < rectangle.x + rectangle.r_width)
			mlx_pixel_put(data->mlx, data->win, j++, i, rectangle.color);
		i++;
	}
	return (0);
}

int render(t_mlx *data)
{
	render_rectangle(data, (t_rectangle){WIDTH - 100, HEIGHT -100, 50, 50, GREEN_COLOR});
	render_rectangle(data, (t_rectangle){0, 0, 80, 80, RED_COLOR});
	return (0);
}

int main (void)
{
	t_mlx data;

	data.mlx = mlx_init();
	if (data.mlx == NULL)
	{
		return (MLX_ERROR);
	}
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "So_long");
	if (data.win == NULL)
	{
		free(data.win);
		return (MLX_ERROR);
	}
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, 2, 1L<<0, key_close, &data);
	
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}