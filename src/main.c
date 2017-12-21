/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabgrall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 15:26:30 by eabgrall          #+#    #+#             */
/*   Updated: 2017/12/01 19:25:12 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			data_check(char *str)
{
	if (!(*str >= '0' && *str <= '9'))
		return (0);
	return (1);
}

void			init_map(t_env *e, t_map *map, const char *file)
{
	int		fd;
	char		*line;
	char		**tmp;

	(void)map;
	if ((fd = open(file, O_RDONLY)) == -1)
		checkout(e, strerror(errno));
	while (get_next_line(fd, &line))
	{
		if (!(tmp = ft_strsplit(line, ' ')))
			checkout(e, "ft_strsplit() error.");
		if (!(tmp[0]) || !(ft_foreachstr(tmp, &data_check)))
			checkout(e, "ft_check_data() error.");
	}
}

int			main(int ac, char **av)
{
	(void)ac;
	t_env		e;

	e.mlx.win = NULL;
	e.mlx.img = NULL;
	e.map.block = NULL;
	e.map.w = 0;
	e.map.h = 0;
	init_map(&e, &(e.map), av[1]);
	init_env(&e);
	hello_world(&e);
	mlx_key_hook(e.mlx.win, key_hook, &e);
	mlx_hook(e.mlx.win, 2, 0, key_pressed, &e);
	mlx_loop(e.mlx.mlx);
	return (0);
}

