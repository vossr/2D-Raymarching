/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/15 13:22:18 by rpehkone         ###   ########.fr       */
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

void	player_movement(t_float_xy *pos, t_float_xy *camera, t_float_xy *camera_tan)
{
	static t_int_xy		last_cursor = {.x = 0, .y = 0};
	t_int_xy		cursor;

	if (is_key_down(126))
		pos->x += camera->x;
	if (is_key_down(126))
		pos->y += camera->y;
	if (is_key_down(123))
		pos->x += camera_tan->x;
	if (is_key_down(123))
		pos->y += camera_tan->y;
	if (is_key_down(125))
		pos->x -= camera->x;
	if (is_key_down(125))
		pos->y -= camera->y;
	if (is_key_down(124))
		pos->x -= camera_tan->x;
	if (is_key_down(124))
		pos->y -= camera_tan->y;
	cursor = get_cursor();
	rotate(camera, (last_cursor.x - cursor.x) * .01);
	rotate(camera_tan, (last_cursor.x - cursor.x) * .01);
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
void	raycast(t_float_xy pos, t_float_xy camera, t_float_xy camera_tan)
{
	static int	**map = NULL;
	t_float_xy	cast;

	if (!map)
		map = read_map(NULL);
	int x = 0;
	t_float_xy color;

	while (x < 1280)
	{
		color.x = 0xFFFFFF;
		color.y = 0xFFFFFF;
		cast = pos;
		cast.x += camera_tan.x * .1 * (x + 1 - 640);
		cast.y += camera_tan.y * .1 * (x + 1 - 640);
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
		stop.y = 360 - 10000 / dist;
		//printf("%f\n", 360.0 - (10000 / dist));

		color.x = 0xFFFFFF - (10000 / dist);
		color.y = 0xFFFFFF - (10000 / dist);
		print_line(start, stop, color);
		stop.y = 360 + 10000 / dist;
		print_line(start, stop, color);
		x++;
	}
	//printf("j = %d\n", 1000 / j);
}

int		wolf(void)
{
	static t_float_xy	pos = {.x = 10, .y = 10};
	static t_float_xy	camera = {.x = 0, .y = .1};
	static t_float_xy	camera_tan = {.x = .1, .y = 0};

	if (is_key_down(53))
		exit(0);
	player_movement(&pos, &camera, &camera_tan);

	t_float_xy relative_camera;
	relative_camera.x = pos.x + camera.x * 100;
	relative_camera.y = pos.y + camera.y * 100;

	t_float_xy color;
	color.x = 0xFF00;
	color.y = 0xFF00;

	raycast(pos, camera, camera_tan);
	print_line(pos, relative_camera, color);
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			if (i == 0 || i == 19 || j == 0 || j == 19)
				pixel_put(i, j, 0xFF0000);
	return (0);
}
