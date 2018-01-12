#include "wolf3d.h"

void			render(t_env *e)
{
	t_thread	t;
	
	thread_process(e, &t);
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.img, 0, 0);
	img_fill(e, ft_frgba(0, 0, 0, 0));
}

int			main(int ac, char **av)
{
	(void)ac;
	t_env		e;

	init_env(&e, av[1]);
	render(&e);
	hello_world(&e);
	mlx_hook(e.mlx.win, 2, 0, &key_pressed, &e);
	mlx_hook(e.mlx.win, 3, 0, &key_released, &e);
	mlx_hook(e.mlx.win, 17, 0, &red_cross, &e);
	mlx_loop_hook(e.mlx.mlx, &key_loop, &e);
	mlx_loop(e.mlx.mlx);
	pthread_exit(NULL);
	return (0);
}
