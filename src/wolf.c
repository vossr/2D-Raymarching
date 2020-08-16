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

void	megapixel_put(int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			pixel_put(x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	rotate(t_float_xy *vertex, double angle)
{
	double	sin_angle;
	double	cos_angle;
	float	x;
	float	y;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	x = vertex->x;
	y = vertex->y;
	vertex->x = x * cos_angle + y * sin_angle;
	vertex->y = y * cos_angle - x * sin_angle;
}

void	player_movement(t_float_xy *location, t_float_xy *direction, t_int_xy map_size)
{
	static t_int_xy		last_cursor = {.x = 0, .y = 0};
	t_int_xy		cursor;

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
	cursor = get_cursor();
	rotate(direction, (last_cursor.x - cursor.x) * .01);
	last_cursor = cursor;
}

int	**read_map(char *str, t_int_xy *map_size)
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

void	raycast(t_float_xy pos, t_float_xy camera, int **map)
{
	t_float_xy	cast;

	int x = 0;
	t_float_xy color;

	const int wall_height = 1000000;
	while (x < 1280)
	{
		color.x = 0xFFFFFF;
		color.y = 0xFFFFFF;
		cast = pos;
			rotate(&camera, 0.001);
		int dist = 0;
		while (map[(int)cast.x][(int)cast.y] != 1)
		{
			cast.x += camera.x;
			cast.y += camera.y;
			dist++;
		}
		if (!dist)
			dist = 1;
		t_float_xy start;
		t_float_xy stop;
		start.x = 1279 - x;
		start.y = 360;
		stop.x = 1279 - x;
		stop.y = 360 - wall_height / dist;
		if ((int)cast.x < (int)(cast.x - camera.x))
		{
			color.x = 0xFFFFFF;
			color.y = 0xFFFFFF;
		}
		else if ((int)cast.y < (int)(cast.y - camera.y))
		{
			color.x = 0xFF0000;
			color.y = 0xFF0000;
		}
		else if ((int)cast.y > (int)(cast.y - camera.y))
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
		stop.y = 360 + wall_height / dist;
		print_line(start, stop, color);
		x++;
	}
}

void	map_print(t_float_xy location, t_float_xy direction, t_int_xy map_size, int **map)
{
	t_float_xy	color;
	int			x;
	int			y;

	color.x = 0xFF00;
	color.y = 0xFF00;
	location.x *= 8;
	location.y *= 8;
	direction.x = location.x + 20000 * direction.x;
	direction.y = location.y + 20000 * direction.y;
	print_line(location, direction, color);
	y = 0;
	while (y < map_size.y)
	{
		x = 0;
		while (x < map_size.x)
		{
			if (map[y][x] == 1)
				megapixel_put(x * 8, y * 8, 0x10FFFFFF);
			x++;
		}
		y++;
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
