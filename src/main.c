/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/19 19:09:02 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		**read_map(char *str, t_int_xy *get_map_size)
{
	static int		**map = NULL;
	static t_int_xy	map_size;
	int				x;
	int				y;

	if (!str)
	{
		get_map_size->x = map_size.x;
		get_map_size->y = map_size.y;
		return (map);
	}
	map_size.x = 20;
	map_size.y = 20;
	map = (int**)malloc(sizeof(int*) * map_size.y);
	y = 0;
	while (y < 20)
	{
		map[y] = (int*)malloc(sizeof(int) * map_size.x);
		x = 0;
		while (x < 20)
		{
			if (y == 0 || y == 19 || x == 0 || x == 19)
				map[y][x] = 1;
			else
				map[y][x] = 0;
			x++;
		}
		y++;
	}
	map[4][4] = 1;
	map[4][6] = 2;
	map[2][2] = 2;
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
