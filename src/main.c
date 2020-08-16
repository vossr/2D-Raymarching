/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/15 13:22:41 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		**read_map(char *str, t_int_xy *map_size)
{
	static int	**map = NULL;
	int		i;
	int		j;

	map_size->x = 20;
	map_size->y = 20;
	(void)str;
	map = (int**)malloc(sizeof(int*) * 20);
	i = 0;
	while (i < 20)
	{
		map[i] = (int*)malloc(sizeof(int) * 20);
		j = 0;
		while (j < 20)
		{
			if (i == 0 || i == 19 || j == 0 || j == 19)
				map[i][j] = 1;
			else
				map[i][j] = 0;
			j++;
		}
		i++;
	}
	map[4][4] = 1;
	return (map);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("usage: ");
		ft_putstr(argv[0]);
		ft_putstr(" [file ...]\n");
	}
	init_window(1280, 720, "Wolf3D");
	return (0);
}
