#include "wolf3d.h"

static char		*stock_map_name(const char *name)
{
	int		i;

	i = 0;
	while (ft_isspace(name[i]) && name[i])
		i++;
	if (!name[i])
		return (NULL);
	return (ft_strdup((char *)&name[i]));
}

static int		stock_map_info(t_env *e, const char *line)
{
	if (ft_strstr(line, "#name:"))
	{
		if (!(e->map.name = stock_map_name(&line[6])))
			return (-1);
	}
	else if (ft_strstr(line, "#width:"))
	{
		if (!(e->map.w = ft_atoi(&line[7])))
			return (-1);
	}
	else if (ft_strstr(line, "#height:"))
	{
		if (!(e->map.h = ft_atoi(&line[8])))
			return (-1);
	}
	else if (ft_strstr(line, "#texture:"))
		return (1);
	else if (ft_strstr(line, "==="))
		return (2);
	return (-1);
}

int			get_map_info(t_env *e, const int fd)
{
	int		ret;
	char		*line;

	while (get_next_line(fd, &line))
	{
		if ((ret = stock_map_info(e, line)) == -1)
			return (0);
		free(line);
		if (ret)
			break;
	}
	if (!(e->map.w) || !(e->map.h) || e->map.w > 50 || e->map.h > 50)
		return (0);
	e->map.max = e->map.w * e->map.h;
	return (ret);
}
