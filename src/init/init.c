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

void			init_env(t_env *e)
{
	if (!(e->mlx.mlx = mlx_init()))
		checkout(e, "Error: mlx_init().");
	if (!(e->mlx.win = mlx_new_window(e->mlx.mlx, WIDTH, HEIGHT
					, e->map.name ? e->map.name : "No name.")))
		checkout(e, "Error: mlx_new_window().");
	if (!(e->mlx.img = mlx_new_image(e->mlx.mlx, WIDTH, HEIGHT)))
		checkout(e, "Error: mlx_new_image().");
	e->mlx.adr = mlx_get_data_addr(e->mlx.img, &(e->mlx.bpp)
			, &(e->mlx.sln), &(e->mlx.end));
}

void			init_map(t_env *e, const char *file)
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