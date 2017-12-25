#include "wolf3d.h"

void			checkout(t_env *e, char *s)
{
	if (s)
		ft_putendl(s);
	if (e->mlx.img)
		mlx_destroy_image(e->mlx.mlx, e->mlx.img);
	if (e->mlx.win)
		mlx_destroy_window(e->mlx.mlx, e->mlx.win);
	if (e->map.name)
		free(e->map.name);
	if (e->map.block)
		free(e->map.block);
	exit(0);
}

void			show_map_block(t_map *map)
{
	int		x;
	int		y;
	int		i;
	
	i = 0;
	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			ft_printf("[%d]", map->block[i]);
			i++;
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

void			hello_world(t_env *e)
{
	int		i;
	int		j;
	t_frgba		col;
	t_frgba		tmp;

	j = HEIGHT - 1;
	tmp.a = 0;
	while (j >= 0)
	{
		i = WIDTH -1;
		while (i >= 0)
		{
			col.r = (float)i / (float)WIDTH;
			col.g = (float)j / (float)HEIGHT;
			col.b = 0.2;
			tmp.r = col.r * 255.99;
			tmp.g = col.g * 255.99;
			tmp.b = col.b * 255.99;
			img_pixel_put(e, i, j, tmp);	
			i--;
		}
		j--;
	}
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.img, 0, 0);
}
