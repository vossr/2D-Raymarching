/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 19:47:35 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/06 11:05:50 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	texture_offsets(t_float_xy direction, t_float_xy cast,
									int *wall_dir, float *texture_x)
{
	if ((int)cast.x != (int)(cast.x - direction.x) &&
				(int)cast.y != (int)(cast.y - direction.y))
	{
		return ;
	}
	else if ((int)cast.x < (int)(cast.x - direction.x))
	{
		*wall_dir = 0;
		*texture_x = 1.0 - (cast.y - (int)cast.y);
	}
	else if ((int)cast.y < (int)(cast.y - direction.y))
	{
		*wall_dir = 1;
		*texture_x = cast.x - (int)cast.x;
	}
	else if ((int)cast.y > (int)(cast.y - direction.y))
	{
		*wall_dir = 2;
		*texture_x = 1.0 - (cast.x - (int)cast.x);
	}
	else
	{
		*wall_dir = 3;
		*texture_x = cast.y - (int)cast.y;
	}
}

void	raycast(t_settings *settings)
{
	t_float_xy		cast;
	t_float_xy		line;
	int				cast_length;
	int				wall_dir;
	float			tex_x;

	wall_dir = 0;
	tex_x = 0;
	t_float_xy direction = settings->direction;
	int x = 0;
	while (x++ <= WIN_WIDTH / 2)
		rotate(&direction, -FOV);
	x = 0;
	while (x < WIN_WIDTH)
	{
		cast = settings->location;
		rotate(&direction, FOV);
		cast_length = 1;
		while (settings->map[(int)cast.y][(int)cast.x] != 1)
		{
			cast.x += direction.x;
			cast.y += direction.y;
			cast_length++;
		}
		texture_offsets(direction, cast, &wall_dir, &tex_x);
		line.x = WIN_HEIGHT / 2 - WMOD / cast_length;
		line.y = WIN_HEIGHT / 2 + WMOD / cast_length;
		put_texture(WIN_WIDTH - 1 - x, line, wall_dir, tex_x);
		x++;
	}
}
