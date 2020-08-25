/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 15:26:27 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/25 22:31:39 by rpehkone         ###   ########.fr       */
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
		if (buf[i] != '\n' && buf[i] != 'n' && buf[i] != '^' && buf[i] != '<' &&
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

void	get_next_map(char *filename, t_int_xy *map_size, char ***map)
{
	int y;

	if (map[0])
	{
		y = 0;
		while (y < map_size->y)
		{
			free(map[0][y]);
			y++;
		}
		free(map[0]);
	}
	y = 0;
	map_size->x = 0;
	map_size->y = 0;
	read_map_size(filename, map_size);
	map[0] = (char**)malloc(sizeof(char*) * map_size->y);
	y = 0;
	while (y < map_size->y)
	{
		map[0][y] = (char*)malloc(sizeof(char) * map_size->x);
		y++;
	}
	set_map(filename, map_size, map[0]);
}

void	read_map(char **argv, t_settings *settings, int next)
{
	static char		**argv2;
	static t_int_xy	map_size;
	static char		**map = NULL;
	static int		i = 1;

	if (argv)
		argv2 = argv;
	if (next)
	{
		if (argv2[i] == NULL)
			fatal_error("no more maps");
		else
		{
			get_next_map(argv2[i], &map_size, &map);
			//check_map(map, map_size);
		}
		i++;
	}
	if (settings)
	{
		settings->map_size.x = map_size.x;
		settings->map_size.y = map_size.y;
		settings->map = map;
		set_start(settings);
	}
}
