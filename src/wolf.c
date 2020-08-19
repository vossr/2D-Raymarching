/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/19 19:15:53 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	rotate(t_float_xy *direction, double angle)
{
	double	sin_angle;
	double	cos_angle;
	float	x;
	float	y;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	x = direction->x;
	y = direction->y;
	direction->x = x * cos_angle + y * sin_angle;
	direction->y = y * cos_angle - x * sin_angle;
}

static void	player_movement(t_float_xy *location,
					t_float_xy *direction, t_int_xy map_size)
{
	if (is_key_down(126))
		location->x += direction->x * 100;
	if (is_key_down(126))
		location->y += direction->y * 100;
	if (is_key_down(125))
		location->x -= direction->x * 100;
	if (is_key_down(125))
		location->y -= direction->y * 100;
	if (location->x < 1.1)
		location->x = 1.1;
	else if (location->x > map_size.x - 1.1)
		location->x = map_size.x - 1.1;
	if (location->y < 1.1)
		location->y = 1.1;
	else if (location->y > map_size.y - 1.1)
		location->y = map_size.y - 1.1;
	if (is_key_down(124))
		rotate(direction, -0.05);
	if (is_key_down(123))
		rotate(direction, 0.05);
}

#include <stdio.h>
static void	texture_offsets(t_float_xy direction,
				t_float_xy cast, int wall_height, int x, int texture_id)
{
	t_float_xy	line;

	line.x = WIN_HEIGHT / 2 - wall_height;
	line.y = WIN_HEIGHT / 2 + wall_height;
	if ((int)cast.x < (int)(cast.x - direction.x))
	{
		put_texture(x, line, texture_id + 0, 1.0 - (cast.y - (int)cast.y));
	}
	else if ((int)cast.y < (int)(cast.y - direction.y))
	{
		put_texture(x, line, texture_id + 1, cast.x - (int)cast.x);
	}
	else if ((int)cast.y > (int)(cast.y - direction.y))
	{
		put_texture(x, line, texture_id + 2, 1.0 - (cast.x - (int)cast.x));
	}
	else
	{
		put_texture(x, line, texture_id + 3, cast.y - (int)cast.y);
	}
}

static void	raycast(t_float_xy location, t_float_xy direction, int **map)
{
	t_float_xy	cast;
	int			x;
	int			cast_length;
	static float fov = 0.00163625;
	static int	wmod = 310000;

	if (is_key_down(18))
		wmod += 10000;
	if (is_key_down(19))
		wmod -= 10000;
	if (is_key_down(20))
		fov += 0.0001;
	if (is_key_down(21))
		fov -= 0.0001;
	printf("fov = %f\n", fov);
	printf("wmod = %d\n", wmod);
	rotate(&direction, -1 * fov * (WIN_WIDTH / 2));
	x = 0;
	while (x < WIN_WIDTH)
	{
		cast = location;
		rotate(&direction, fov);
		cast_length = 1;
		while (map[(int)cast.x][(int)cast.y] == 0)
		{
			cast.x += direction.x;
			cast.y += direction.y;
			cast_length++;
		}
		texture_offsets(direction, cast, wmod / cast_length,
		WIN_WIDTH - x - 1, (map[(int)cast.x][(int)cast.y] - 1) * 4);
		x++;
	}
}

int			wolf(void)
{
	static t_float_xy	location = {.x = 10, .y = 10};
	static t_float_xy	direction = {.x = 0.0, .y = .001};
	static t_int_xy		map_size;
	static int			**map = NULL;

	if (is_key_down(53))
		exit(0);
	else if (!map)
		map = read_map(NULL, &map_size);
	player_movement(&location, &direction, map_size);
	raycast(location, direction, map);
	map_print(location, map_size, map);
	update_image();
	fps();
	return (0);
}
