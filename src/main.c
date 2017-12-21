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

int			pr(char *str)
{
	ft_printf("%s\n", str);
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
		if (!(tmp[0]) || !(ft_foreachstr(tmp, &pr)))
			checkout(e, "ft_check_data() error.");

	}
}

int			main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_env		e;

	init_map(&e, &(e.map), av[1]);
	init_env(&e);
	mlx_key_hook(e.mlx.win, key_hook, &e);
	mlx_hook(e.mlx.win, 2, 0, key_pressed, &e);
	mlx_loop(e.mlx.mlx);
	return (0);
}

