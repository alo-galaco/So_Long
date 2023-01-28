#include "../includes/so_long.h"
#include <X11/keysym.h>

#define MLX_ERROR 1
#define RED_COLOR 0xFF0000
#define GREEN_COLOR 0x0000FFCC
#define WHITE_COLOR 0x00FFFFFF

typedef struct s_rectangle
{
	int x;
	int y;
	int r_width;
	int r_height;
	int r_color;
}				t_rectangle;

typedef struct s_img
{
	void	*mlx_img;
	char	*address;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}				t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}				t_data;

int key_close(int keysym, t_data *data)
{
	printf("\nkey close 00\n");
	if (keysym == XK_Escape)
	{	
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	printf("Keypress: %d\n", keysym);
	return (0);
	printf("\nkey close end\n");
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->address + (y * img->line_lenght + x * (img->bits_per_pixel / 8));
	*(int *)pixel = color;
}

int	render_rectangle(t_img *img, t_rectangle rectangle)
{
	printf("\nrender rectangle 00\n");
	int i;
	int j;

	i = rectangle.y;
	while (i < rectangle.y + rectangle.r_height)
	{
		j = rectangle.x;
		while (j < rectangle.x + rectangle.r_width)
			img_pix_put(img, j++, i, rectangle.r_color);
		++i;
	}
	return (0);
	printf("\nrender rectangle end\n");
}

void	render_background(t_img *img, int color)
{
	printf("\nrenderbackgroun 00\n");
	int	i;
	int	j;
	
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			img_pix_put(img, j++, i, color);
		++i;
	}
	printf("\nrenderbackgroun end\n");
}

int render(t_data *data)
{
	printf("\nrender\n");
	if (data->win_ptr == NULL)
		return (1);
	printf("\nrendererror\n");
	render_background(&data->img, WHITE_COLOR);
	printf("\nrenderback\n");
	render_rectangle(&data->img, (t_rectangle){WIDTH - 100, HEIGHT -100, 50, 50, GREEN_COLOR});
	render_rectangle(&data->img, (t_rectangle){0, 0, 80, 80, RED_COLOR});
	printf("\nrenderfunction\n");
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

// int main (void)
// {
// 	t_mlx data;

// 	data.mlx = mlx_init();
// 	if (data.mlx == NULL)
// 	{
// 		return (MLX_ERROR);
// 	}
// 	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "So_long");
// 	if (data.win == NULL)
// 	{
// 		free(data.win);
// 		return (MLX_ERROR);
// 	}
// 	mlx_loop_hook(data.mlx, &render, &data);
// 	mlx_hook(data.win, 2, 1L<<0, key_close, &data);
	
// 	mlx_loop(data.mlx);
// 	mlx_destroy_display(data.mlx);
// 	free(data.mlx);
// }

int main (void)
{
	t_data data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "So_long");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.address = mlx_get_data_addr(data.img.mlx_img, &data.img.bits_per_pixel, &data.img.line_lenght, &data.img.endian);
	// mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	// img_pix_put(&data.img, 10, 10, RED_COLOR);
	// printf("\nmain pix put\n");
	// mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);
	// printf("\nput image na janela\n");
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, 2, 1L<<0, key_close, &data);
	mlx_loop(data.mlx_ptr);
	printf("\nloop\n");
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}