/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 19:07:18 by alngo             #+#    #+#             */
/*   Updated: 2017/11/29 21:43:49 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		move(t_env *e, int key)
{
	t_map	map;
	t_cam	cam;
	double	moveSpeed = 0.5;

	map = e->map;
	cam = e->cam;
	if (key == W_KEY)
	{
		if(map.block[(int)(cam.pos.y * map.w + cam.pos.x + cam.dir.x * moveSpeed)] == 0)
			e->cam.pos.x = cam.pos.x + cam.dir.x * moveSpeed;
		if(map.block[(int)((cam.pos.y + cam.dir.y * moveSpeed) * map.w + cam.pos.x)] == 0)
			e->cam.pos.y = cam.pos.y + cam.dir.y * moveSpeed;
	}
	if (key == S_KEY)
	{
		if(map.block[(int)(cam.pos.y * map.w + cam.pos.x - cam.dir.x * moveSpeed)] == 0)
			e->cam.pos.x = cam.pos.x - cam.dir.x * moveSpeed;
		if(map.block[(int)((cam.pos.y - cam.dir.y * moveSpeed) * map.w + cam.pos.x)] == 0)
			e->cam.pos.y = cam.pos.y - cam.dir.y * moveSpeed;
	}
	render(e);
}

void		rotate(t_env *e, int key)
{
	t_cam	cam;
	double	olddirx;
	double	oldplanex;
	double	rotSpeed = M_PI / 8;

	cam = e->cam;
	olddirx = cam.dir.x;
	oldplanex = cam.plane.x;
	if (key == D_KEY)
	{
		e->cam.dir.x = cam.dir.x * cos(-rotSpeed) - cam.dir.y * sin(-rotSpeed);
		e->cam.dir.y = olddirx * sin(-rotSpeed) + cam.dir.y * cos(-rotSpeed);
		e->cam.plane.x = cam.plane.x * cos(-rotSpeed) - cam.plane.y * sin(-rotSpeed);
		e->cam.plane.y = oldplanex * sin(-rotSpeed) + cam.plane.y * cos(-rotSpeed);
	}
	if (key == A_KEY)
	{
		e->cam.dir.x = cam.dir.x * cos(rotSpeed) - cam.dir.y * sin(rotSpeed);
		e->cam.dir.y = olddirx * sin(rotSpeed) + cam.dir.y * cos(rotSpeed);
		e->cam.plane.x = cam.plane.x * cos(rotSpeed) - cam.plane.y * sin(rotSpeed);
		e->cam.plane.y = oldplanex * sin(rotSpeed) + cam.plane.y * cos(rotSpeed);
	}
	render(e);
}

int				key_pressed(int key, t_env *e)
{
	if (key == ECHAP_KEY)
		checkout(e, "Bye bye !");
	else if (key == W_KEY || key == S_KEY)
		move(e, key);
	else if (key == A_KEY || key == D_KEY)
		rotate(e, key);
	else
		ft_printf("[%d]\n", key);
	return (0);
}
