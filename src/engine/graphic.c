/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 18:37:30 by alngo             #+#    #+#             */
/*   Updated: 2018/01/16 18:38:19 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			img_pixel_put(t_env *e, int x, int y, t_frgba c)
{
	int		i;
	t_mlx	mlx;

	mlx = e->mlx;
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

void			img_fill(t_env *e, t_frgba c)
{
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			img_pixel_put(e, x, y, c);
			x++;
		}
		y++;
	}
}

void			hello_world(t_env *e)
{
	int			i;
	int			j;
	t_frgba		col;
	t_frgba		tmp;

	j = HEIGHT - 1;
	tmp.a = 0;
	while (j >= 0)
	{
		i = WIDTH - 1;
		while (i >= 0)
		{
			col.r = (float)i / (float)WIDTH;
			col.g = (float)j / (float)HEIGHT;
			col.b = 0.2;
			tmp.r = col.r * 255.99;
			tmp.g = col.g * 255.99;
			tmp.b = col.b * 255.99;
			img_pixel_put(e, i, j, tmp);
			i--;
		}
		j--;
	}
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.img, 0, 0);
}
