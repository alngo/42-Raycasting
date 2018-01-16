/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 18:26:41 by alngo             #+#    #+#             */
/*   Updated: 2018/01/16 18:27:33 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			floor_cast(t_env *e, int x, int id)
{
	t_frgba		floor_color;
	t_frgba		ceil_color;
	int			y;

	floor_color = ft_frgba(30, 30, 30, 0);
	ceil_color = ft_frgba(80, 100, 255, 0);
	if (e->line[id].end.y < 0)
		e->line[id].end.y = HEIGHT;
	y = e->line[id].end.y;
	while (y < HEIGHT)
	{
		img_pixel_put(e, x, y, floor_color);
		img_pixel_put(e, x, HEIGHT - y, ceil_color);
		y++;
	}
}
