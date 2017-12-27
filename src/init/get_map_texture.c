#include "wolf3d.h"

static int	stock_tex_data(t_env *e, char **data)
{
	static int	index;
	while (*data)
	{
		if (index == e->map.tex.len)
			break;
		printf("%s\n", *data);
		free(*data);
		data++;
		index++;
	}
	return (index);

}

static int	get_tex_data(t_env *e, const int fd)
{
	char	*line;
	char	**tmp;

	(void)e;
	while (get_next_line(fd, &line))
	{
		if (!(tmp = ft_strsplit(line, '	')))
			return (0);
		free(line);
		if (!(stock_tex_data(e, tmp)))
			return (0);
		free(tmp);
	}
	return (1);
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
	return (0);
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
		if (!(e->map.tex.number = (int *)ft_memalloc(sizeof(int) * e->map.tex.len)))
			return (0);
		if (!(e->map.tex.tex = (int **)ft_memalloc(sizeof(int *) * e->map.tex.len)))
			return (0);
		if ((ret = get_tex_data(e, fd)) == -1)
			return (0);
	}
	return (ret);
}
