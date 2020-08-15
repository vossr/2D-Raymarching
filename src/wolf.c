/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/15 17:53:55 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	megapixel_put(int x, int y, int color)
{
	pixel_put(x + 0, y + 0, color);
	pixel_put(x + 0, y + 1, color);
	pixel_put(x + 0, y + 2, color);
	pixel_put(x + 0, y + 3, color);
	pixel_put(x + 1, y + 0, color);
	pixel_put(x + 1, y + 1, color);
	pixel_put(x + 1, y + 2, color);
	pixel_put(x + 1, y + 3, color);
	pixel_put(x + 2, y + 0, color);
	pixel_put(x + 2, y + 1, color);
	pixel_put(x + 2, y + 2, color);
	pixel_put(x + 2, y + 3, color);
	pixel_put(x + 3, y + 0, color);
	pixel_put(x + 3, y + 1, color);
	pixel_put(x + 3, y + 2, color);
	pixel_put(x + 3, y + 3, color);
}

//void	camera()

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

void	player_movement(t_float_xy *pos, t_float_xy *camera)
{
	static t_int_xy		last_cursor = {.x = 0, .y = 0};
	t_int_xy		cursor;

	if (is_key_down(126))
		pos->x += camera->x * 100;
	if (is_key_down(126))
		pos->y += camera->y * 100;
	if (is_key_down(125))
		pos->x -= camera->x * 100;
	if (is_key_down(125))
		pos->y -= camera->y * 100;
	cursor = get_cursor();
	rotate(camera, (last_cursor.x - cursor.x) * .01);
	last_cursor = cursor;
}

int	**read_map(char *str)
{
	static int	**map = NULL;
	int		i;
	int		j;

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

//1280
void	raycast(t_float_xy pos, t_float_xy camera)
{
	static int	**map = NULL;
	t_float_xy	cast;

	if (!map)
		map = read_map(NULL);
	int x = 0;
	t_float_xy color;

	const int wall_height = 1000000;
	//t_float_xy camera_cpy = camera;
	while (x < 1280)
	{
		color.x = 0xFFFFFF;
		color.y = 0xFFFFFF;
		cast = pos;
		//if (x < 1280 / 2)
			rotate(&camera, 0.001);
		/*
		else
		{
			static int asd = 1;
			if (asd)
			{
				asd = 0;
				camera = camera_cpy;
			}
			rotate(&camera, 0.001);
		}
		*/
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
		//printf("%f\n", 360.0 - (wall_height / dist));

		color.x = 0xFFFFFF - (wall_height / dist);
		color.y = 0xFFFFFF - (wall_height / dist);
		print_line(start, stop, color);
		stop.y = 360 + wall_height / dist;
		print_line(start, stop, color);
		x++;
	}
	//printf("j = %d\n", 1000 / j);
}

void	map(t_float_xy pos, t_float_xy camera)
{
	t_float_xy	relative_camera;
	t_float_xy	color;
	int			x;
	int			y;

	color.x = 0xFF00;
	color.y = 0xFF00;
	relative_camera.x = pos.x + camera.x * 100;
	relative_camera.y = pos.y + camera.y * 100;
	pos.x *= 4;
	pos.y *= 4;
	relative_camera.x *= 4;
	relative_camera.y *= 4;
	print_line(pos, relative_camera, color);
	y = 0;
	while (y < 20)
	{
		x = 0;
		while (x < 20)
		{
			if (x == 0 || x == 19 || y == 0 || y == 19)
				megapixel_put(x * 4, y * 4, 0xaaaaaa);
			x++;
		}
		y++;
	}
}

int		wolf(void)
{
	static t_float_xy	pos = {.x = 10, .y = 10};
	static t_float_xy	camera = {.x = 0, .y = .001};

	if (is_key_down(53))
		exit(0);
	player_movement(&pos, &camera);
	raycast(pos, camera);
	map(pos, camera);
	update_image();
	return (0);
}
