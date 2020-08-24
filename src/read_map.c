/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 15:26:27 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/24 17:02:43 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	set_map(char *filename, t_int_xy *map_size, char **map)
{
	t_int_xy	coord;
	char		buf[10001];
	int			fd;
	int			i;

	ft_memset(&buf, 0, 10001);
	fd = open(filename, O_RDONLY);
	read(fd, buf, 10000);
	i = 0;
	coord.y = 0;
	while (coord.y < map_size->y)
	{
		coord.x = 0;
		while (coord.x < map_size->x)
		{
			map[coord.y][coord.x] = buf[i];
			coord.x++;
			i++;
		}
		i++;
		coord.y++;
	}
}

void	read_map_size(char *filename, t_int_xy *map_size)
{
	char	buf[10001];
	int		fd;
	int		i;

	ft_memset(&buf, 0, 10001);
	if (2 > (fd = open(filename, O_RDONLY)))
		fatal_error(ft_strjoin("error reading ", filename));
	if (!read(fd, buf, 10000))
		fatal_error(ft_strjoin("error reading ", filename));
	i = 0;
	while (buf[i])
	{
		if (buf[i] != '\n' && buf[i] != '^' && buf[i] != '<' &&
			buf[i] != 'v' && buf[i] != '>' && (buf[i] > '9' || buf[i] < '0'))
			fatal_error(ft_strjoin("error reading ", filename));
		i++;
	}
	i = 0;
	while (buf[i])
		if (buf[i++] == '\n')
			map_size->y++;
	i = 0;
	while (buf[i++] != '\n')
		map_size->x++;
}

void	read_map(char *str, t_settings *settings)
{
	static t_int_xy	map_size;
	static char		**map = NULL;
	int				y;

	if (!str)
	{
		settings->map_size.x = map_size.x;
		settings->map_size.y = map_size.y;
		settings->map = map;
		settings->menu = 0;
		settings->fps = 0;
		settings->print_map = 0;
		settings->cs_mode = 0;
		set_start(settings);
		return ;
	}
	read_map_size(str, &map_size);
	map = (char**)malloc(sizeof(char*) * map_size.y);
	y = 0;
	while (y < map_size.y)
	{
		map[y] = (char*)malloc(sizeof(char) * map_size.x);
		y++;
	}
	set_map(str, &map_size, map);
}
