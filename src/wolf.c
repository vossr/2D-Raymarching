/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/15 19:16:27 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	rotate(t_float_xy *direction, double angle)
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

void	player_movement(t_float_xy *location, t_float_xy *direction, t_int_xy map_size)
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

void	raycast(t_float_xy location, t_float_xy direction, int **map)
{
	t_float_xy	cast;

	int x = 0;
	t_float_xy color;

	const int wall_height = 1000000;
	while (x < WIN_WIDTH)
	{
		color.x = 0xFFFFFF;
		color.y = 0xFFFFFF;
		cast = location;
			rotate(&direction, 0.001);
		int dist = 0;
		while (map[(int)cast.x][(int)cast.y] != 1)
		{
			cast.x += direction.x;
			cast.y += direction.y;
			dist++;
		}
		if (!dist)
			dist = 1;
		t_float_xy start;
		t_float_xy stop;
		start.x = WIN_WIDTH - 1 - x;
		stop.x = start.x;
		start.y = WIN_HEIGHT / 2;
		stop.y = WIN_HEIGHT / 2 - wall_height / dist;
		if ((int)cast.x < (int)(cast.x - direction.x))
		{
			color.x = 0xFFFFFF;
			color.y = 0xFFFFFF;
		}
		else if ((int)cast.y < (int)(cast.y - direction.y))
		{
			color.x = 0xFF0000;
			color.y = 0xFF0000;
		}
		else if ((int)cast.y > (int)(cast.y - direction.y))
		{
			color.x = 0xFF00;
			color.y = 0xFF00;
		}
		else
		{
			color.x = 0xFF;
			color.y = 0xFF;
		}
		print_line(start, stop, color);
		stop.y = WIN_HEIGHT / 2 + wall_height / dist;
		print_line(start, stop, color);
		x++;
	}
}

int		wolf(void)
{
	static t_float_xy	location = {.x = 10, .y = 10};
	static t_float_xy	direction = {.x = 0, .y = .001};
	static t_int_xy		map_size;
	static int			**map = NULL;

	if (is_key_down(53))
		exit(0);
	else if (!map)
		map = read_map(NULL, &map_size);
	player_movement(&location, &direction, map_size);
	raycast(location, direction, map);
	map_print(location, direction, map_size, map);
	update_image();
	return (0);
}
