/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/20 15:03:03 by rpehkone         ###   ########.fr       */
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
			map[coord.y][coord.x] = ft_atoi(&buf[i]);
			while (buf[i] && buf[i] >= '0' && buf[i] <= '9')
				i++;
			while (buf[i] && (buf[i] < '0' || buf[i] > '9'))
				i++;
			coord.x++;
		}
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
		if (buf[i] != ' ' && buf[i] != '\n' && (buf[i] > '9' || buf[i] < '0'))
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
		while (buf[i] != '\n' && buf[i] >= '0' && buf[i] <= '9')
			i++;
		while (buf[i] != '\n' && (buf[i] < '0' || buf[i] > '9'))
			i++;
		map_size->x++;
	}
}

#include <stdio.h>
int		**read_map(char *str, t_int_xy *get_map_size)
{
	static int		**map = NULL;
	static t_int_xy	map_size;
	int				y;

	if (!str)
	{
		get_map_size->x = map_size.x;
		get_map_size->y = map_size.y;
		return (map);
	}
	read_map_size(str, &map_size);
	printf("x = %d\n", map_size.x);
	printf("y = %d\n", map_size.y);
	map = (int**)malloc(sizeof(int*) * map_size.y);
	y = 0;
	while (y < map_size.y)
	{
		map[y] = (int*)malloc(sizeof(int) * map_size.x);
		y++;
	}
	set_map(str, &map_size, map);
	return (NULL);
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
