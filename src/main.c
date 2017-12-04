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

#include "rtv1.h"

int				main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_env			e;

	init_env(&e);
	mlx_key_hook(e.mlx.win, key_hook, &e);
	mlx_hook(e.mlx.win, 2, 0, key_pressed, &e);
	mlx_loop(e.mlx.mlx);
	return (0);
}

