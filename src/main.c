#include "wolf3d.h"

int			main(int ac, char **av)
{
	(void)ac;
	t_env		e;

	e.mlx.win = NULL;
	e.mlx.img = NULL;
	e.map.block = NULL;
	e.map.name = NULL;
	e.map.w = 0;
	e.map.h = 0;
	init_map(&e, av[1]);
	init_env(&e);
	hello_world(&e);
	mlx_hook(e.mlx.win, 2, 0, key_pressed, &e);
	mlx_loop(e.mlx.mlx);
	return (0);
}

