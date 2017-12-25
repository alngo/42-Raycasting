#include "wolf3d.h"

void	move(t_env *e, int key)
{
	t_vec2d	new_pos;

	if (key == W_KEY)
	{
		new_pos.x = e->cam.pos.x + e->cam.dir.x * SPEED;
		new_pos.y = e->cam.pos.y + e->cam.dir.y * SPEED;
	}
	else if (key == S_KEY)
	{
		new_pos.x = e->cam.pos.x - e->cam.dir.x * SPEED;
		new_pos.y = e->cam.pos.y - e->cam.dir.y * SPEED;
	}
	if (new_pos.y * e->map.w + new_pos.x < e->map.max)
	{
		if (e->map.block[(int)((int)new_pos.y * e->map.w + (int)new_pos.x)] == 0)
		{
			e->cam.pos.x = new_pos.x;
			e->cam.pos.y = new_pos.y;
		}
	}
}

void		strafe(t_env *e, int key)
{
	double	rot;
	t_vec2d	tmp;
	t_vec2d	new_pos;

	rot = M_PI / 2;
	tmp.x = e->cam.dir.x * cos(-rot) - e->cam.dir.y * sin(-rot);
	tmp.y = e->cam.dir.x * sin(-rot) + e->cam.dir.y * cos(-rot);
	if (key == D_KEY)
	{
		new_pos.x = e->cam.pos.x + tmp.x * (SPEED / 2);
		new_pos.y = e->cam.pos.y + tmp.y * (SPEED / 2);
	}                                         
	else if (key == A_KEY)                              
	{                         
		new_pos.x = e->cam.pos.x - tmp.x * (SPEED / 2);
		new_pos.y = e->cam.pos.y - tmp.y * (SPEED / 2);
	}
	if (new_pos.y * e->map.w + new_pos.x < e->map.max)
	{
		if (e->map.block[(int)((int)new_pos.y * e->map.w + (int)new_pos.x)] == 0)
		{
			e->cam.pos.x = new_pos.x;
			e->cam.pos.y = new_pos.y;
		}
	}
}

void		rotate(t_env *e, int key)
{
	t_cam	cam;
	double	olddirx;
	double	oldplanex;
	double	rotSpeed = M_PI / 50;

	cam = e->cam;
	olddirx = cam.dir.x;
	oldplanex = cam.plane.x;
	if (key == RIGHT_KEY)
	{
		e->cam.dir.x = cam.dir.x * cos(-rotSpeed) - cam.dir.y * sin(-rotSpeed);
		e->cam.dir.y = olddirx * sin(-rotSpeed) + cam.dir.y * cos(-rotSpeed);
		e->cam.plane.x = cam.plane.x * cos(-rotSpeed) - cam.plane.y * sin(-rotSpeed);
		e->cam.plane.y = oldplanex * sin(-rotSpeed) + cam.plane.y * cos(-rotSpeed);
	}
	else if (key == LEFT_KEY)
	{
		e->cam.dir.x = cam.dir.x * cos(rotSpeed) - cam.dir.y * sin(rotSpeed);
		e->cam.dir.y = olddirx * sin(rotSpeed) + cam.dir.y * cos(rotSpeed);
		e->cam.plane.x = cam.plane.x * cos(rotSpeed) - cam.plane.y * sin(rotSpeed);
		e->cam.plane.y = oldplanex * sin(rotSpeed) + cam.plane.y * cos(rotSpeed);
	}
}
