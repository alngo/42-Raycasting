#include "wolf3d.h"

static void		line_init_calc(t_ray *ray, t_line *line, int x)
{
	line->height = HEIGHT / ray->wall;
	line->start.y = -line->height / 2 + HEIGHT / 2;
	if (line->start.y < 0)
		line->start.y = 0;
	line->end.y = line->height / 2 + HEIGHT / 2;
	if (line->end.y > HEIGHT)
		line->end.y = HEIGHT;
	line->start.x = x;
	line->end.x = x;
	line->side = ray->side;
}

static void		line_set_basic_color(t_line *line, int block)
{
	if (block == 1)
		line->col = ft_frgba(255, 0, 0, 0);
	else if (block == 2)
		line->col = ft_frgba(0, 255, 0, 0);
	else if (block == 3)
		line->col = ft_frgba(0, 0, 255, 0);
	else if (block == 4)
		line->col = ft_frgba(255, 255, 255, 0);
	else
		line->col = ft_frgba(50, 50, 50, 0);
}

static void		line_set_text_num(t_env *e, t_line *line, int block)
{
	int		i;

	i = 0;
	while (i < e->map.tex.len)
	{
		if (block == e->map.tex.number[i])
			break;
		i++;
	}
	line->tex_nu = i == e->map.tex.len ? 0 : i;
}

static void		line_get_type(t_env *e, t_line *line, int *mapx, int *mapy)
{
	int		block;

	block = e->map.block[*mapy * e->map.w + *mapx];
	if (!e->map.texture)
		line_set_basic_color(line, block);
	else
		line_set_text_num(e, line, block);
}

void			line_cast(t_env *e, int x, int id)
{
	line_init_calc(&e->ray[id], &e->line[id], x);
	line_get_type(e, &e->line[id], &e->ray[id].mapx, &e->ray[id].mapy);
	if (!e->map.texture)
		line_basic_draw(e, &e->line[id]);
	else
		line_textu_draw(e, &e->line[id], &e->ray[id]);
}
