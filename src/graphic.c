/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 19:07:22 by alngo             #+#    #+#             */
/*   Updated: 2017/12/01 18:51:40 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			pixel_put(t_env *px, int x, int y, t_frgba c)
{
	int		i;
	t_mlx	mlx;

	mlx = px->mlx;
	i = (mlx.sln * y) + (x * (mlx.bpp / 8));
	if (mlx.end == 1)
	{
		mlx.adr[i] = c.r;
		mlx.adr[i + 1] = c.g;
		mlx.adr[i + 2] = c.b;
		mlx.adr[i + 3] = c.a;
	}
	else
	{
		mlx.adr[i] = c.b;
		mlx.adr[i + 1] = c.g;
		mlx.adr[i + 2] = c.r;
		mlx.adr[i + 3] = c.a;
	}
}
