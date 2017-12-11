/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 19:07:26 by alngo             #+#    #+#             */
/*   Updated: 2017/11/29 22:37:17 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			checkout(t_env *e, char *s)
{
	if (e->mlx.img)
		mlx_destroy_image(e->mlx.mlx, e->mlx.img);
	if (e->mlx.win)
		mlx_destroy_window(e->mlx.mlx, e->mlx.win);
	if (s)
		ft_putendl(s);
	exit(0);
}
