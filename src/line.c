#include "wolf3d.h"

static void		line_init_calc(t_ray *ray, t_line *line, int x)
{
	int		height;

	height = HEIGHT / ray->wall;
	line->start.y = -height / 2 + HEIGHT / 2;
	if (line->start.y < 0)
		line->start.y = 0;
	line->end.y = height / 2 + HEIGHT / 2;
	if (line->end.y > HEIGHT)
		line->end.y = HEIGHT;
	line->start.x = x;
	line->end.x = x;
	line->side = ray->side;
}


static void		line_get_color(t_map *map, t_line *line, int *mapx, int *mapy)
{
	if (map->block[*mapy * map->w + *mapx] == 1)
		line->col = ft_frgba(255, 0, 0, 0);
	else if (map->block[*mapy * map->w + *mapx] == 2)
		line->col = ft_frgba(0, 255, 0, 0);
	else if (map->block[*mapy * map->w + *mapx] == 3)
		line->col = ft_frgba(0, 0, 255, 0);
	else if (map->block[*mapy * map->w + *mapx] == 4)
		line->col = ft_frgba(255, 255, 255, 0);
	else 
		line->col = ft_frgba(50, 50, 50, 0);
	if (line->side)
		line->col = shadow(line->col);
}

void			line_cast(t_env *e, int *mapx, int *mapy, int x)
{
	line_init_calc(&e->ray, &e->line, x);
	line_get_color(&e->map, &e->line, mapx, mapy);
	line_draw(e, &e->line);
}
