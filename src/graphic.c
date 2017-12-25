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

void			line_draw(t_env *e, t_line *line)
{
	int		x;
	int		y;
	
	x = line->start.x;
	y = line->start.y;
	while (y < line->end.y)
	{
		img_pixel_put(e, x, y, line->col);
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
