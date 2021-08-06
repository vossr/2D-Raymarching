/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 19:47:35 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/06 13:25:07 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	texture_mapper(t_float_xy direction, t_float_xy cast,
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

void	raycast(t_settings *settings)//const? not pointer?
{
	int				x;
	t_float_xy		cast;
	t_float_xy		step;
	t_float_xy		line;
	int				wall_dir;
	float			tex_x;

	float ray_angle = settings->angle - FOV / 2;

	wall_dir = 0;
	tex_x = 0;
	x = 0;
	while (x < WIN_WIDTH)
	{
		step.x = sinf(deg_to_rad(ray_angle)) / RAY_PREC;
		step.y = cosf(deg_to_rad(ray_angle)) / RAY_PREC;
		cast = settings->location;
		while (settings->map[(int)cast.y][(int)cast.x] != 1)
		{
			cast.x += step.x;
			cast.y += step.y;
		}
		texture_mapper(step, cast, &wall_dir, &tex_x);
		cast.x -= settings->location.x;
		cast.y -= settings->location.y;
		float dist = sqrt(cast.x * cast.x + cast.y * cast.y) * cos(deg_to_rad(ray_angle - settings->angle));
		line.x = WIN_HEIGHT / 2 - WIN_HEIGHT / 2 / dist;
		line.y = WIN_HEIGHT / 2 + WIN_HEIGHT / 2 / dist;
		put_texture(WIN_WIDTH - 1 - x, line, wall_dir, tex_x);
		ray_angle += FOV / WIN_WIDTH;
		x++;
	}
}
