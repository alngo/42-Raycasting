/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 18:15:29 by alngo             #+#    #+#             */
/*   Updated: 2018/01/16 18:56:19 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			line_basic_draw(t_env *e, t_line *line, int x)
{
	int			y;
	t_frgba		col;

	y = line->start.y;
	col = line->col;
	while (y < line->end.y)
	{
		img_pixel_put(e, x, y, col);
		y++;
	}
}

t_frgba			shadow(t_frgba col)
{
	t_frgba		ret;

	ret.r = col.r / 2;
	ret.g = col.g / 2;
	ret.b = col.b / 2;
	ret.a = col.a;
	return (ret);
}

void			line_textu_draw(t_env *e, t_line *line, t_ray *ray, int x)
{
	int			y;
	t_frgba		pix_col;
	t_mlx		tmp;
	t_vec2d		textu;
	t_vec2d		tool;

	tmp.adr = mlx_get_data_addr(e->map.tex.tex[line->tex_nu]
			, &tmp.bpp, &tmp.sln, &tmp.end);
	tool.x = line->side ? ray->pos.x + ray->wall * ray->dir.x :
						ray->pos.y + ray->wall * ray->dir.y;
	tool.x -= (int)tool.x;
	textu.x = (int)(tool.x * TEXTURE_WIDTH);
	if ((!line->side && ray->dir.x > 0) || (line->side && ray->dir.y < 0))
		textu.x = TEXTURE_WIDTH - textu.x - 1;
	y = line->start.y;
	while (++y < line->end.y)
	{
		tool.y = y * 256 - HEIGHT * 128 + line->height * 128;
		textu.y = ((tool.y * TEXTURE_HEIGHT) / line->height) / 256;
		pix_col = ft_inttofrgba(((int *)tmp.adr)[(int)textu.y
				* TEXTURE_WIDTH + (int)textu.x] << 8);
		pix_col = line->orientation == WEST ? shadow(pix_col) : pix_col;
		img_pixel_put(e, x, y, pix_col);
	}
}
