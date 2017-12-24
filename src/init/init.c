/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 19:06:55 by alngo             #+#    #+#             */
/*   Updated: 2017/11/29 22:32:02 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void		init_map(t_env *e, const char *file)
{
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		checkout(e, strerror(errno));
	if (!(get_map_info(e, fd)))
		checkout(e, "get_map_info() error..");
	if (!(get_map_block(e, fd)))
		checkout(e, "get_map_block() error.");
	close(fd);
}

static	void		init_cam(t_env *e, t_cam *cam, t_map *map)
{
	int		max;
	t_ldiv		div;

	max = map->max - 1;
	while (max >= 0)
	{
		if (map->block[max] == 0)
			break;
		max--;
	}
	if (max == -1)
		checkout(e, "init_cam() error.");
	div = ft_ldiv(max, map->w);
	cam->pos.y = (double)div.quot;
	cam->pos.x = (double)div.rem;
	cam->dir.y = 0;
	cam->dir.x = -1;

	cam->plane.y = 0.66;
	cam->plane.x = 0;
}

void			init_env(t_env *e, const char *file)
{
	init_map(e, file);
	init_cam(e, &e->cam, &(e->map));
	if (!(e->mlx.mlx = mlx_init()))
		checkout(e, "Error: mlx_init().");
	if (!(e->mlx.win = mlx_new_window(e->mlx.mlx, WIDTH, HEIGHT
					, e->map.name ? e->map.name : "No name.")))
		checkout(e, "Error: mlx_new_window().");
	if (!(e->mlx.img = mlx_new_image(e->mlx.mlx, WIDTH, HEIGHT)))
		checkout(e, "Error: mlx_new_image().");
	e->mlx.adr = mlx_get_data_addr(e->mlx.img, &(e->mlx.bpp)
			, &(e->mlx.sln), &(e->mlx.end));
	ft_printf("Init done !\nMap:\n");
	show_map_block(&e->map);
	ft_printf("Camera position:\n[%d][%d]\n", (int)e->cam.pos.x, (int)e->cam.pos.y);
}

void			init_null_secure(t_env *e)
{
	e->mlx.win = NULL;
	e->mlx.img = NULL;
	e->mlx.adr = NULL;
	e->map.block = NULL;
	e->map.name = NULL;
	e->map.w = 0;
	e->map.h = 0;
	e->map.max = 0;
}
