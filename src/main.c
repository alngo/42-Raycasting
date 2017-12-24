#include "wolf3d.h"

void			ray_init_calc(t_ray *ray, t_cam *cam, int x)
{
	double		cam_x;
	double		sqr_dir_x;
	double		sqr_dir_y;

	cam_x = 2 * x / (double)WIDTH - 1;
	ray->pos.x = cam->pos.x;
	ray->pos.y = cam->pos.y;
	ray->dir.x = cam->dir.x + cam->plane.x * cam_x;
	ray->dir.y = cam->dir.y + cam->plane.y * cam_x;
	sqr_dir_x = ray->dir.x * ray->dir.x;
	sqr_dir_y = ray->dir.y * ray->dir.y;
	ray->d_delta.x = sqrt(1 + sqr_dir_y / sqr_dir_x);
	ray->d_delta.y = sqrt(1 + sqr_dir_x / sqr_dir_y);
	ray->hit = false;
}

void			ray_step_calc(t_ray *ray, int *mapx, int *mapy)
{
	*mapx = (int)ray->pos.x;
	*mapy = (int)ray->pos.y;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->d_side.x = (ray->pos.x - *mapx) * ray->d_delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->d_side.x = (*mapx + 1.0 - ray->pos.x) * ray->d_delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->d_side.y = (ray->pos.y - *mapy) * ray->d_delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->d_side.y = (*mapy + 1.0 - ray->pos.y) * ray->d_delta.y;
	}
}

void			ray_cast_dda(t_ray *ray, t_map *map, int *mapx, int *mapy)
{
	while (ray->hit == false)
	{
		if (ray->d_side.x < ray->d_side.y)
		{
			ray->d_side.x = ray->d_side.x + ray->d_delta.x;
			*mapx = *mapx + ray->step.x;
			ray->side = false;
		}
		else
		{
			ray->d_side.y = ray->d_side.y + ray->d_delta.y;
			*mapy = *mapy + ray->step.y;
			ray->side = true;
		}
		if (map->block[*mapy * map->w + *mapx] > 0)
			ray->hit = true;
	}
}

void			ray_wall_calc(t_ray *ray, int *mapx, int *mapy)
{
	if (ray->side)
		ray->wall = (*mapy - ray->pos.y + (1 - ray->step.y) / 2) / ray->dir.y;
	else
		ray->wall = (*mapx - ray->pos.x + (1 - ray->step.x) / 2) / ray->dir.x;
}

void			line_init_calc(t_ray *ray, t_line *line, int x)
{
	int		height;

	height = HEIGHT / ray->wall;
	line->start.y = -height / 2 + HEIGHT / 2;
	if (line->start.y < 0)
		line->start.y = 0;
	line->end.y = height / 2 + HEIGHT / 2;
	if (line->end.y < 0)
		line->end.y = HEIGHT - 1;
	line->start.x = x;
	line->end.x = x;
	line->side = ray->side;
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

void			line_get_color(t_map *map, t_line *line, int *mapx, int *mapy)
{
	if (map->block[*mapy * map->w + *mapx] == 1)
		line->col = ft_frgba(255, 0, 0, 0);
	else if (map->block[*mapy * map->w + *mapx] == 2)
		line->col = ft_frgba(0, 255, 0, 0);
	else if (map->block[*mapy * map->w + *mapx] == 3)
		line->col = ft_frgba(0, 0, 255, 0);
	else if (map->block[*mapy * map->w + *mapx] == 4)
		line->col = ft_frgba(255, 255, 255, 0);
	else if (map->block[*mapy * map->w + *mapx] == 5)
		line->col = ft_frgba(255, 255, 0, 0);
	if (line->side)
		line->col = shadow(line->col);
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

void			render(t_env *e)
{
	int		mapx;
	int		mapy;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		ray_init_calc(&e->ray, &e->cam, x);
		ray_step_calc(&e->ray, &mapx, &mapy);
		ray_cast_dda(&e->ray, &e->map, &mapx, &mapy);
		ray_wall_calc(&e->ray, &mapx, &mapy);
		line_init_calc(&e->ray, &e->line, x);
		line_get_color(&e->map, &e->line, &mapx, &mapy);
		line_draw(e, &e->line);
		x++;
	}
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.img, 0, 0);
	img_fill(e, ft_frgba(0, 0, 0, 0));
}

int			main(int ac, char **av)
{
	(void)ac;
	t_env		e;

	init_env(&e, av[1]);
	render(&e);
	mlx_hook(e.mlx.win, 2, 0, key_pressed, &e);
	mlx_loop(e.mlx.mlx);
	return (0);
}
