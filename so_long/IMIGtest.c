#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

t_img	*make_img(void *mlx, char *img_path)
{
	t_img *img = malloc(sizeof(t_img));

	img->img_ptr = mlx_xpm_file_to_image(mlx, img_path, &img->w, &img->h);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);

	return (img);
}


int	main(void)
{
	void	*mlx;
	void	*win_ptr;
	void	*img;
	t_img	*img_type;
	char	*img_path = "./imgs/wall.xpm";
	int img_w;
	int img_h;

	mlx = mlx_init();

	img_type = make_img(mlx, img_path);
	printf("WDT: %i; HEIGHT: %i\n\n", img_type->w, img_type->h);

	win_ptr = mlx_new_window(mlx, img_type->w * 2, img_type->h * 2, "YAY");


	mlx_put_image_to_window(mlx, win_ptr, img_type->img_ptr, 0,0);
	mlx_put_image_to_window(mlx, win_ptr, img_type->img_ptr, img_type->w,0);
	mlx_put_image_to_window(mlx, win_ptr, img_type->img_ptr, 0,img_type->h);
	mlx_put_image_to_window(mlx, win_ptr, img_type->img_ptr, img_type->w,img_type->h);

	mlx_loop(mlx);
	return (0);
}
