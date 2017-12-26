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

t_frgba			shadow(t_frgba col)
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

void			line_textu_draw(t_env *e, t_line *line)
{
	double		wall_x;
	int		textu_x;
	int		textu_y;
	int		d;
	t_frgba		pix_col;
	int		y;
	int		x;

	if (e->line.side)
		wall_x = e->ray.pos.x + e->ray.wall * e->ray.dir.x;
	else
		wall_x = e->ray.pos.y + e->ray.wall * e->ray.dir.y;
	wall_x -= (int)wall_x;
	textu_x = (int)(wall_x * TEXTURE_WIDTH);
	if (!line->side && e->ray.dir.x > 0)
		textu_x = TEXTURE_WIDTH - textu_x - 1;
	if (line->side && e->ray.dir.y < 0)
		textu_x = TEXTURE_WIDTH - textu_x - 1;
	x = line->start.x;
	y = line->start.y;
	while (y < line->end.y)
	{
		d = y * 256 - HEIGHT * 128 + line->height * 128;
		textu_y = ((d * TEXTURE_HEIGHT) / line->height) / 256;
		pix_col = 
		ft_inttofrgba(e->texture.texture[line->texture_number][TEXTURE_WIDTH *
		textu_y + textu_x] << 8);
		if (line->side)
			pix_col = shadow(pix_col);
		img_pixel_put(e, x, y, pix_col);
		y++;
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
