/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 15:26:27 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/06 14:49:30 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	set_map(char *filename, t_settings *settings)
{
	int i;

	settings->map_height = 10;
	settings->map_width = 10;
	if (!(settings->map = (char**)malloc(sizeof(char*) * settings->map_height)))
		fatal_error("map allocation failed");
	i = 0;
	while (i < settings->map_height)
	{
		if (!(settings->map[i] = (char*)malloc(sizeof(char) * settings->map_width)))
			fatal_error("map allocation failed");
		if (!i || i == settings->map_height - 1)
			ft_memset(settings->map[i], 1, settings->map_width);
		else
			ft_memset(settings->map[i], 0, settings->map_width);
		settings->map[i][0] = 1;
		settings->map[i][settings->map_width - 1] = 1;
		i++;
	}
	settings->map[5][5] = 1;
	(void)filename;
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
		if (buf[i] != '\n' && buf[i] != '1' && buf[i] != '2' && buf[i] != '0')
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

void	check_map_validity(t_settings *settings)
{
	int		x;
	int		y;

	y = 0;
	while (y < settings->map_height)
	{
		x = 0;
		while (x < settings->map_width)
		{
			if (!x || !y || x == settings->map_width - 1 || y == settings->map_height - 1)
			{
				if (settings->map[y][x] != 1)
					fatal_error("invalid map edge");
			}
			else if (settings->map[y][x] != 1)
			{
				settings->location.x = x;
				settings->location.y = y;
			}
			x++;
		}
		y++;
	}
	if (settings->location.x == 0 || settings->location.y == 0)
		fatal_error("no empty space in map");
}

t_settings	*read_map(char *filename)
{
	static t_settings *settings;

	if (!filename)
		return (settings);
	if (!(settings = (t_settings*)malloc(sizeof(t_settings))))
		fatal_error("map allocation failed");
	ft_memset(settings, 0, sizeof(t_settings));
	set_map(filename, settings);
	check_map_validity(settings);
	return (NULL);
}
