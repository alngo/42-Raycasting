#include "wolf3d.h"

static t_frgba		shadow(t_frgba col)
{
	t_frgba		ret;

	ret.r = col.r / 2;
	ret.g = col.g / 2;
	ret.b = col.b / 2;
	ret.a = col.a;
	return (ret);
}

void			line_basic_draw(t_env *e, t_line *line)
{
	int		x;
	int		y;
	t_frgba		col;

	x = line->start.x;
	y = line->start.y;
	col = line->side ? shadow(line->col) : line->col;
	while (y < line->end.y)
	{
		img_pixel_put(e, x, y, col);
		y++;
	}
}

void			line_textu_draw(t_env *e, t_line *line, t_ray *ray)
{
	double		wall_x;
	int			textu_x;
	int			textu_y;
	int			d;
	t_frgba		pix_col;
	int			y;
	int			x;
	char		*ptr;
	int			bpp;
	int			sln;
	int			end;

	ptr = mlx_get_data_addr(e->map.tex.tex[line->tex_nu], &bpp, &sln, &end);
	if (line->side)
		wall_x = ray->pos.x + ray->wall * ray->dir.x;
	else
		wall_x = ray->pos.y + ray->wall * ray->dir.y;
	wall_x -= (int)wall_x;
	textu_x = (int)(wall_x * TEXTURE_WIDTH);
	if (!line->side && ray->dir.x > 0)
		textu_x = TEXTURE_WIDTH - textu_x - 1;
	if (line->side && ray->dir.y < 0)
		textu_x = TEXTURE_WIDTH - textu_x - 1;
	x = line->start.x;
	y = line->start.y;
	while (y < line->end.y)
	{
		d = y * 256 - HEIGHT * 128 + line->height * 128;
		textu_y = ((d * TEXTURE_HEIGHT) / line->height) / 256;
		pix_col = ft_inttofrgba(((int *)ptr)[textu_y * TEXTURE_WIDTH + textu_x]);
		if (line->side)
			pix_col = shadow(pix_col);
		img_pixel_put(e, x, y, pix_col);
		y++;
	}
}
