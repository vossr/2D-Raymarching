/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wolf3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/12 22:01:42 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

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

void	rotate(t_double_xy *vertex, double angle)
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

void	wolf3D(void)
{
	static t_double_xy	pos = {.x = 100, .y = 100};
	static t_double_xy	camera = {.x = 0, .y = 100};
	static t_double_xy	camera_tan = {.x = 100, .y = 0};
	static t_int_xy		last_cursor = {.x = 0, .y = 0};
	t_int_xy		cursor;

	if (is_key_down(53))
		exit(0);
	if (is_key_down(126))
	{
		pos.x += camera.x / 100;
		pos.y += camera.y / 100;
	}
	if (is_key_down(123))
	{
		pos.x += camera_tan.x / 100;
		pos.y += camera_tan.y / 100;
	}
	if (is_key_down(125))
	{
		pos.x -= camera.x / 100;
		pos.y -= camera.y / 100;
	}
	if (is_key_down(124))
	{
		pos.x -= camera_tan.x / 100;
		pos.y -= camera_tan.y / 100;
	}

	cursor = get_cursor();
	rotate(&camera, (last_cursor.x - cursor.x) * .01);
	rotate(&camera_tan, (last_cursor.x - cursor.x) * .01);
	last_cursor = cursor;

	pixel_put(pos.x, pos.y, 0xFFFFFF);
	pixel_put(pos.x + camera.x, pos.y + camera.y, 0xFFFF00);
	pixel_put(pos.x + camera_tan.x, pos.y + camera_tan.y, 0x00FF00);
}
