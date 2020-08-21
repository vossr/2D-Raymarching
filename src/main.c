/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/20 16:52:37 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	set_map(char *filename, t_int_xy *map_size, int **map)
{
	t_int_xy	coord;
	char	buf[10001];
	int		fd;
	int		i;

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
			//älä muuta intiks
			map[coord.y][coord.x] = buf[i] - '0';
			coord.x++;
			i++;
		}
		i++;
		coord.y++;
	}
}

#include <stdio.h>
void	parse_error(char *filename)
{
	printf("error reading %s\n", filename);
	exit(0);
}

void	read_map_size(char *filename, t_int_xy *map_size)
{
	char	buf[10001];
	int		fd;
	int		i;

	ft_memset(&buf, 0, 10001);
	if (2 > (fd = open(filename, O_RDONLY)))
		parse_error(filename);
	if (!read(fd, buf, 10000))
		parse_error(filename);
	i = 0;
	while (buf[i])
	{
		if (buf[i] != '\n' && buf[i] != '^' && buf[i] != '<' && buf[i] != 'v' && buf[i] != '>' && (buf[i] > '9' || buf[i] < '0'))
			parse_error(filename);
		i++;
	}
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			map_size->y++;
		i++;
	}
	i = 0;
	while (buf[i] != '\n')
	{
		i++;
		map_size->x++;
	}
}

void	set_start_direction(t_settings *settings, int c)
{
	if (c == '^' - '0')
	{
		settings->direction.x = 0.0;
		settings->direction.y = -0.001;
	}
	else if (c == '<' - '0')
	{
		settings->direction.x = -0.001;
		settings->direction.y = 0.0;
	}
	else if (c == 'v' - '0')
	{
		settings->direction.x = 0.0;
		settings->direction.y = 0.001;
	}
	else if (c == '>' - '0')
	{
		settings->direction.x = 0.001;
		settings->direction.y = 0.0;
	}
}

void	set_start(t_settings *settings)
{
	int x;
	int y;
	int c;

	y = 0;
	while (y < settings->map_size.y)
	{
		x = 0;
		while (x < settings->map_size.x)
		{
			c = settings->map[y][x];
			if (c == '^' - '0' || c == '<' - '0' ||
					c == 'v' - '0' || c == '>' - '0')
			{
				settings->location.x = x + .5;
				settings->location.y = y + .5;
				set_start_direction(settings, c);
				return ;
			}
			x++;
		}
		y++;
	}
	//set to first free position
	settings->location.x = 1.5;
	settings->location.y = 1.5;
	settings->direction.x = 0.0;
	settings->direction.y = 0.001;
}

void	read_map(char *str, t_settings *settings)
{
//read to char arraya
	static int		**map = NULL;
	static t_int_xy	map_size;
	int				y;

	if (!str)
	{
		settings->map_size.x = map_size.x;
		settings->map_size.y = map_size.y;
		settings->map = map;
		settings->menu = 0;
		set_start(settings);
		return ;
	}
	read_map_size(str, &map_size);
	map = (int**)malloc(sizeof(int*) * map_size.y);
	y = 0;
	while (y < map_size.y)
	{
		map[y] = (int*)malloc(sizeof(int) * map_size.x);
		y++;
	}
	set_map(str, &map_size, map);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("usage: ");
		ft_putstr(argv[0]);
		ft_putstr(" [file ...]\n");
	}
	else
	{
		read_map(argv[1], NULL);
		init_window(WIN_WIDTH, WIN_HEIGHT, "Wolf3D");
	}
	return (0);
}
