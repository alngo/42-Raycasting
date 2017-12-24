#include "wolf3d.h"

static int		check_map_block(char *str)
{
	if (!(ft_foreachar(str, &ft_isdigit)))
		return (0);
	return (1);
}

static int		stock_map_block(t_env *e, char **data)
{
	static int	index;

	if (!ft_foreachstr(data, &check_map_block))
		return (0);
	while (*data)
	{
		if (index == e->map.max)
			break;
		e->map.block[index] = ft_atoi(*data);
		free(*data);
		data++;
		index++;
	}
	return (1);
}

int			get_map_block(t_env *e, const int fd)
{
	char		*line;
	char		**tmp;

	if (!(e->map.block = (int *)ft_memalloc(sizeof(int) * e->map.max)))
		return (0);
	while (get_next_line(fd, &line))
	{
		if (!(tmp = ft_strsplit(line, ' ')))
			return (0);
		free(line);
		if (!(stock_map_block(e, tmp)))
			return (0);
		free(tmp);
	}
	return (1);
}
