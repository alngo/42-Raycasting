#include "wolf3d.h"

void			render(t_env *e)
{
	int		mapx;
	int		mapy;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		ray_cast(e, &mapx, &mapy, x);
		line_cast(e, &mapx, &mapy, x);
		x++;
	}
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.img, 0, 0);
	img_fill(e, ft_frgba(0, 0, 0, 0));
}

void			init_hard_texture(t_hard_texture *texture)
{
	int		x;
	int		y;
	int 		xorcolor;
	int		xcolor;
	int		ycolor;
	int 		xycolor;

	y = 0;
	while (y < TEXTURE_HEIGHT)
	{
		x = 0;
		while (x < TEXTURE_WIDTH)
		{
			xorcolor = (x * 256 / TEXTURE_WIDTH) ^ (y * 256 / TEXTURE_HEIGHT);
			xcolor = x * 256 / TEXTURE_HEIGHT;
			ycolor = y * 256 / TEXTURE_HEIGHT;
			xycolor = y * 128 / TEXTURE_HEIGHT + x * 128 / TEXTURE_WIDTH;
			texture->texture[0][TEXTURE_WIDTH * y + x] = 65536 * 254 * (x != y && x != TEXTURE_WIDTH - y);
			texture->texture[1][TEXTURE_WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			texture->texture[2][TEXTURE_WIDTH * y + x] = 256 * xycolor + 65536 * xycolor;
			texture->texture[3][TEXTURE_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			texture->texture[4][TEXTURE_WIDTH * y + x] = 256 * xorcolor;
			texture->texture[5][TEXTURE_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16);
			texture->texture[6][TEXTURE_WIDTH * y + x] = 65536 * ycolor;
			texture->texture[7][TEXTURE_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128;
			x++;
		}
		y++;
	}
}

int			main(int ac, char **av)
{
	(void)ac;
	t_env		e;

	init_env(&e, av[1]);
	init_hard_texture(&e.texture);
	render(&e);
	mlx_hook(e.mlx.win, 2, 0, &key_pressed, &e);
	mlx_hook(e.mlx.win, 3, 0, &key_released, &e);
	mlx_loop_hook(e.mlx.mlx, &key_loop, &e);
	mlx_loop(e.mlx.mlx);
	return (0);
}
