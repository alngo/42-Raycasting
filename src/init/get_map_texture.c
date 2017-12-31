#include "wolf3d.h"

static int		stock_tex_data(t_env *e, char *line)
{
	static int	index;
	char		*tmp;
	int		w;
	int		h;

	
	if (index == e->map.tex.len)
		return (1);
	tmp = (char *)line;
	e->map.tex.number[index] = ft_atoi(line);
	while (ft_isdigit(*line) || ft_isspace(*line))
		line++;
	if (!(tmp = ft_strjoin(e->map.tex.dir, line)))
		return (0);
	e->map.tex.tex[index] = mlx_xpm_file_to_image(e->mlx.mlx, tmp, &w, &h);
	free(tmp);
	index++;
	return (1);
}


static int		get_tex_data(t_env *e, const int fd)
{
	char		*line;

	(void)e;
	while (get_next_line(fd, &line))
	{
		if (ft_strstr(line, "==="))
		{
			free(line);
			return (1);
		}
		else
		{
			if (!(stock_tex_data(e, line)))
			{
				free(line);
				return (0);
			}
		}
		free(line);
	}
	return (0);
}

static char		*stock_tex_dir(const char *dir)
{
	int		i;

	i = 0;
	while (ft_isspace(dir[i]) && dir[i])
		i++;
	if (!dir[i])
		return (NULL);
	return (ft_strdup((char *)&dir[i]));
}

static int		stock_tex_info(t_env *e, const char *line)
{
	if (ft_strstr(line, "#texture_num:"))
	{
		if (!(e->map.tex.len = ft_atoi(&line[13])))
			return (-1);
	}
	else if (ft_strstr(line, "#texture_dir:"))
	{
		if (!(e->map.tex.dir = stock_tex_dir(&line[13])))
			return (-1);
	}
	else if (ft_strstr(line, "#list:"))
		return (2);
	return (0);
}

int			get_map_texture(t_env *e, const int fd)
{
	char		*line;
	int		ret;

	while (get_next_line(fd, &line))
	{
		if ((ret = stock_tex_info(e, line)) ==  -1)
			return (0);
		free(line);
		if (ret)
			break;
	}
	if (ret == 2)
	{
		if (!(e->map.tex.number = (int *)ft_memalloc(sizeof(int) * e->map.tex.len)))
			return (0);
		if (!(e->map.tex.tex = (void **)ft_memalloc(sizeof(void *) * e->map.tex.len)))
			return (0);
		if ((ret = get_tex_data(e, fd)) == -1)
			return (0);
		e->map.texture = 1;
	}
	return (ret);
}
