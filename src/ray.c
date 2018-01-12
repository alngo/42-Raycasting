#include "wolf3d.h"

static void		ray_init_calc(t_ray *ray, t_cam *cam, int x)
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

static void		ray_step_calc(t_ray *ray, int *mapx, int *mapy)
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

static void		ray_cast_dda(t_ray *ray, t_map *map, int *mapx, int *mapy)
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

static void		ray_wall_calc(t_ray *ray, int *mapx, int *mapy)
{
	if (ray->side)
		ray->wall = (*mapy - ray->pos.y + (1 - ray->step.y) / 2) / ray->dir.y;
	else
		ray->wall = (*mapx - ray->pos.x + (1 - ray->step.x) / 2) / ray->dir.x;
}

void			ray_cast(t_env *e, int x, int id)
{
	ray_init_calc(&e->ray[id], &e->cam, x);
	ray_step_calc(&e->ray[id], &e->ray[id].mapx, &e->ray[id].mapy);
	ray_cast_dda(&e->ray[id], &e->map, &e->ray[id].mapx, &e->ray[id].mapy);
	ray_wall_calc(&e->ray[id], &e->ray[id].mapx, &e->ray[id].mapy);
}
