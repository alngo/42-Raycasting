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

void			show_block(int *arr, int w, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		if (!(i % w) && i)
			ft_printf("\n");
		ft_printf("[%2d]", arr[i]);
		i++;
	}
	ft_printf("\n");
}

