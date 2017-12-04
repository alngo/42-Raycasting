/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabgrall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 15:51:03 by eabgrall          #+#    #+#             */
/*   Updated: 2017/12/01 18:59:25 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "../libft/include/libft.h"
# include "../mlx/mlx.h"
# include "x11.h"

# define WIDTH 	1000
# define HEIGHT 1000
# define TRUE	1
# define FALSE	0

typedef struct		s_mlx
{
	char		*adr;
	int		bpp;
	int		end;
	int		sln;
	void		*img;
	void		*mlx;
	void		*win;
}			t_mlx;

typedef struct		s_env
{
	t_mlx		mlx;
}			t_env;

/*
**	=== main.c ===
*/
void			proceed(t_env *e);
/*
** === graphic.c ===
*/
void			pixel_put(t_env *px, int x, int y, t_frgba c);
/*
** === input.c ===
*/
int			key_hook(int key, t_env *e);
int			key_pressed(int key, t_env *e);
/*
** === utils.c ===
*/
void			checkout(t_env *e, char *s);
/*
** === init.c ===
*/
void			init_env(t_env *e);

#endif
