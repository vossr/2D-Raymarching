/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 12:11:49 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	read_map(char *filename, t_settings *set, int i, int fd)
{
	char	*line;
	int		len;

	while (0 < get_next_line(fd, &line) && ++set->map_height)
		free(line);
	if (get_next_line(fd, &line) < 0)
		fatal_error("file reading failed");
	close(fd);
	set->map = (char **)malloc(sizeof(char *) * set->map_height);
	if (!set->map)
		fatal_error("map allocation failed");
	fd = open(filename, O_RDONLY);
	while (0 < get_next_line(fd, &set->map[i]) && i < set->map_height)
	{
		len = (int)ft_strlen(set->map[i]);
		if (!i)
			set->map_width = len;
		if (set->map_width != len)
			fatal_error("map not square");
		i++;
	}
	if (get_next_line(fd, &line) < 0)
		fatal_error("file reading failed");
	close(fd);
}

static void	check_map_validity(t_settings *set)
{
	int		x;
	int		y;

	y = 0;
	while (y < set->map_height)
	{
		x = -1;
		while (++x < set->map_width)
		{
			set->map[y][x] -= '0';
			if (!x || !y || x == set->map_width - 1 || y == set->map_height - 1)
			{
				if (set->map[y][x] != 1)
					fatal_error("invalid map edge");
			}
			else if (set->map[y][x] == 0)
			{
				set->location.x = x + 0.5;
				set->location.y = y + 0.5;
			}
			else if (set->map[y][x] != 1)
				fatal_error("invalid character in map");
		}
		y++;
	}
}

t_settings	*init(char *filename)
{
	static t_settings	*settings;
	int					fd;

	if (!filename)
		return (settings);
	settings = (t_settings *)malloc(sizeof(t_settings));
	if (!settings)
		fatal_error("map allocation failed");
	ft_memset(settings, 0, sizeof(t_settings));
	fd = open(filename, O_RDONLY);
	read_map(filename, settings, 0, fd);
	check_map_validity(settings);
	if (settings->map_width > 100 || settings->map_height > 100)
		fatal_error("map too slow");
	if (settings->location.x == 0 || settings->location.y == 0)
		fatal_error("no empty space in map");
	return (NULL);
}

void	fatal_error(char *error)
{
	ft_putstr(error);
	ft_putchar('\n');
	exit(0);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putstr("usage: ");
		ft_putstr(argv[0]);
		ft_putstr(" [file ...]\n");
	}
	else
	{
		init(argv[1]);
		init_window(WIN_WIDTH, WIN_HEIGHT, "Wolf3D");
	}
	return (0);
}
