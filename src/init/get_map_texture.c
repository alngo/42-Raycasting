#include "wolf3d.h"

static int	stock_tex_data(t_env *e, const int fd)
{
	char	*line;

	(void)e;
	while (get_next_line(fd, &line))
	{
		ft_printf("%s\n", line);
		if (ft_strstr(line, "==="))
		{
			free(line);
			return (2);
		}
		free(line);
	}
	return (-1);
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

static int	stock_tex_info(t_env *e, const char *line)
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
		return (1);
	return (-1);
}

int		get_map_texture(t_env *e, const int fd)
{
	char	*line;
	int	ret;

	while (get_next_line(fd, &line))
	{
		if ((ret = stock_tex_info(e, line)) ==  -1)
			return (0);
		free(line);
		if (ret)
			break;
	}
	if (ret == 1)
	{
		if ((ret = stock_tex_data(e, fd)) == -1)
			return (0);
	}
	return (ret);
}
