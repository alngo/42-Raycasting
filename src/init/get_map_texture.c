#include "wolf3d.h"

int		get_map_texture(t_env *e, const int fd)
{
	char	*line;

	(void)e;
	while (get_next_line(fd, &line))
	{
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
		if (ft_strstr(line, "==="))
		{
			free(line);
			return (2);
		}
		free(line);
	}
	return (0);
}
