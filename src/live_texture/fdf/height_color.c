/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   height_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 21:00:33 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 19:15:48 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		save_coord(int start_i, int stop_i, int which)
{
	static int save_start = 0;
	static int save_stop = 0;

	if (start_i < 0)
	{
		if (which)
			return (save_stop);
		return (save_start);
	}
	save_start = start_i;
	save_stop = stop_i;
	return (0);
}

int		edit_i_height(int i, int which)
{
	static t_xyz	*map = NULL;
	int				map_i;

	if (!map)
		map = make_map(NULL, NULL, NULL);
	map_i = save_coord(-1, -1, which);
	i += map[map_i].z;
	return (i);
}

int		color_add_height(int color, int which)
{
	double	red;
	double	grn;
	double	blu;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (j < 312)
	{
		i++;
		if (i > 310)
			i = 0;
		red = sin(0.02 * i + 0) * 127 + 128;
		grn = sin(0.02 * i + 2) * 127 + 128;
		blu = sin(0.02 * i + 4) * 127 + 128;
		if (color == ((int)red * 65536 + (int)grn * 256 + (int)blu))
			break ;
		j++;
	}
	i = edit_i_height(i, which);
	red = sin(0.02 * i + 0) * 127 + 128;
	grn = sin(0.02 * i + 2) * 127 + 128;
	blu = sin(0.02 * i + 4) * 127 + 128;
	return ((int)red * 65536 + (int)grn * 256 + (int)blu);
}

t_xyz	add_color_height(t_xyz color)
{
	color.x = color_add_height(color.x, 0);
	color.y = color_add_height(color.y, 1);
	return (color);
}
