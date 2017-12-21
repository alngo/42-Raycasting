#ifndef RTV1_H
# define RTV1_H
# include "../libft/include/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <string.h>
# include "x11.h"

# define WIDTH 	900
# define HEIGHT 600
# define TRUE	1
# define FALSE	0


typedef struct		s_cam
{
	t_vec2d		pos;
	t_vec2d		dir;
	t_vec2d		plane;
}			t_cam;

typedef struct		s_map
{
	int		h;
	int		w;
	int		*dot;
}			t_map;

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
	t_cam		cam;
	t_map		map;
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
