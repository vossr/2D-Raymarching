/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 15:26:27 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/06 15:41:04 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	read_map(char *filename, t_settings *settings)
{
	int		i;
	char	*line;
	int		err;
	int		fd;

	fd = open(filename, O_RDONLY);
	while (0 < (err = get_next_line(fd, &line)) && ++settings->map_height)
		free(line);
	if (err < 0)
		fatal_error("file reading failed");
	close(fd);
	if (!(settings->map = (char**)malloc(sizeof(char*) * settings->map_height)))
		fatal_error("map allocation failed");
	fd = open(filename, O_RDONLY);
	i = 0;
	while (0 < (err = get_next_line(fd, &line)) && i < settings->map_height)
	{
		int len = (int)ft_strlen(line);
		if (!i)
			settings->map_width = len;
		if (settings->map_width != len)
			fatal_error("map not square");
		settings->map[i] = line;
		i++;
	}
	if (err < 0)
		fatal_error("file reading failed");
	close(fd);
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
			settings->map[y][x] -= '0';
			if (!x || !y || x == settings->map_width - 1 || y == settings->map_height - 1)
			{
				if (settings->map[y][x] != 1)
					fatal_error("invalid map edge");
			}
			else if (settings->map[y][x] == 0)
			{
				settings->location.x = x + 0.5;
				settings->location.y = y + 0.5;
			}
			else if (settings->map[y][x] != 1)
				fatal_error("invalid character in map");
			x++;
		}
		y++;
	}
	if (settings->location.x == 0 || settings->location.y == 0)
		fatal_error("no empty space in map");
}

t_settings	*init(char *filename)
{
	static t_settings *settings;

	if (!filename)
		return (settings);
	if (!(settings = (t_settings*)malloc(sizeof(t_settings))))
		fatal_error("map allocation failed");
	ft_memset(settings, 0, sizeof(t_settings));
	read_map(filename, settings);
	check_map_validity(settings);
	return (NULL);
}
