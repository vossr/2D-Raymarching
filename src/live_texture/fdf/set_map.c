/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:06:50 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 20:38:18 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_rest(int *x, int y, int width, t_xyz *map)
{
	int		height;

	y--;
	height = get_map_len(0) / width / 2;
	while ((*x) - y * width < width)
	{
		map[(*x)].x = 50 * (((*x) - (y * width)) - width / 2);
		map[(*x)].y = 50 * (y - height);
		map[(*x)].z = 0;
		(*x)++;
	}
}

void	edit_end(char *line)
{
	int i;

	i = 0;
	while (line[i])
		i++;
	i--;
	while (i > 0 && line[i] == ' ')
		i--;
	i++;
	line[i] = '\0';
}

void	fdf_set_map(t_xyz *map, int fd, int width, int height)
{
	int		x;
	int		y;
	int		i;
	char	*line;

	x = 0;
	y = 0;
	while (!(i = 0) && get_next_line(fd, &line))
	{
		edit_end(line);
		while (line[i])
		{
			map[x].x = 50 * ((x - (y * width)) - width / 2);
			map[x].y = 50 * (y - height);
			map[x].z = -10 * ft_atoi(&line[i]);
			while (line[i] && line[i] == ' ')
				i++;
			while (line[i] && line[i] != ' ')
				i++;
			x++;
		}
		set_rest(&x, ++y, width, map);
		free(line);
	}
}
