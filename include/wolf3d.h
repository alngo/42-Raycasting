#ifndef RTV1_H
# define RTV1_H
# include "../libft/include/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "x11.h"

# define WIDTH 	900
# define HEIGHT 600

typedef struct		s_cam
{
	t_vec2d		pos;
	t_vec2d		dir;
	t_vec2d		plane;
}			t_cam;

typedef struct		s_ray
{
	t_vec2d		pos;
	t_vec2d		dir;
	t_vec2d		d_side;
	t_vec2d		d_delta;
	t_vec2d		step;
	t_bool		hit;
	t_bool		side;
	double		wall;
}			t_ray;

typedef struct		s_line
{
	t_vec2d		start;
	t_vec2d		end;
	t_frgba		col;
	t_bool		side;
}			t_line;

typedef struct		s_map
{
	int		h;
	int		w;
	int		*block;
	int		max;
	char		*name;
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
	t_ray		ray;
	t_line		line;
}			t_env;

/*
** === main.c ===
*/
void			render(t_env *e);
/*
** === ray.c ===
*/
void			ray_cast(t_env *e, int *mapx, int *mapy, int x);
/*
** === line.c ===
*/
void			line_compute(t_env *e, int *mapx, int *mapy, int x);
/*
** === graphic.c ===
*/
void			img_pixel_put(t_env *e, int x, int y, t_frgba c);
void			img_fill(t_env *e, t_frgba c);
void			line_draw(t_env *e, t_line *line);
t_frgba			shadow(t_frgba col);
/*
** === input.c ===
*/
int			key_pressed(int key, t_env *e);
/*
** === utils.c ===
*/
void			checkout(t_env *e, char *s);
void			hello_world(t_env *e);
void			show_map_block(t_map *map);
/*
** === init.c ===
*/
void			init_env(t_env *e, const char *file);
/*
** === init_map_info.c ===
*/
int			get_map_info(t_env *e, const int fd);
/*
** === init_map_block.c ===
*/
int			get_map_block(t_env *e, const int fd);


#endif
