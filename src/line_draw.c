#include "wolf3d.h"

void			line_basic_draw(t_env *e, t_line *line)
{
	int			x;
	int			y;
	t_frgba		col;

	x = line->start.x;
	y = line->start.y;
	col = line->col;
	while (y < line->end.y)
	{
		img_pixel_put(e, x, y, col);
		y++;
	}
}

void			line_textu_draw(t_env *e, t_line *line, t_ray *ray)
{
	double		wall_x;
	int		textu_x;
	int		textu_y;
	int		d;
	t_frgba		pix_col;
	int		y;
	int		x;
	t_mlx		tmp;

	tmp.adr = mlx_get_data_addr(e->map.tex.tex[line->tex_nu], &tmp.bpp, &tmp.sln, &tmp.end);
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
		if (line->side)
			pix_col = ft_inttofrgba(((int *)tmp.adr)[textu_y * TEXTURE_WIDTH + textu_x] << 7 & 2139062016);
		else
			pix_col = ft_inttofrgba(((int *)tmp.adr)[textu_y * TEXTURE_WIDTH + textu_x] << 8);
		img_pixel_put(e, x, y, pix_col);
		y++;
	}
}
