/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:44:10 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/20 17:22:13 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_perspective(t_fdf_settings *settings, t_xyz *start, t_xyz *stop)
{
	float	fov;

	fov = (settings->fov + 2) * 500;
	start->x /= (start->z / fov);
	start->y /= (start->z / fov);
	stop->x /= (stop->z / fov);
	stop->y /= (stop->z / fov);
}

t_xyz	get_color(int set)
{
	static t_xyz	color = {.x = -1};

	if (color.x == -1)
	{
		color.x = 0xFFFFFF;
		color.y = 0xFFFFFF;
		color.z = 0;
	}
	else if (set)
	{
		color.x = set;
		color.y = set;
	}
	return (color);
}

void	move_center(t_xyz *start, t_xyz *stop, t_fdf_settings *settings)
{
	static double	zoom = -1200;
	t_xyz			color;

	if (zoom > 600)
		zoom = 600;
	if (zoom < -4000)
		zoom = -4000;
	start->z -= zoom;
	stop->z -= zoom;
	if (settings->projection_b)
		add_perspective(settings, start, stop);
	start->x += LIVE_TEXTURE_SIZE / 2;
	start->y += LIVE_TEXTURE_SIZE / 2;
	stop->x += LIVE_TEXTURE_SIZE / 2;
	stop->y += LIVE_TEXTURE_SIZE / 2;
	color = add_color_height(settings->color);
	print_line(*start, *stop,
		(unsigned int)color.x, (unsigned int)color.y);
}

void	center_image(t_xyz *start, t_xyz *stop, int reset,
			t_fdf_settings *settings)
{
	static int	x = 0;
	static int	y = 0;

	if (reset)
	{
		x = 0;
		y = 0;
		return ;
	}
	start->x += x;
	start->y += y;
	stop->x += x;
	stop->y += y;
	move_center(start, stop, settings);
}

void	draw(t_xyz *vertices, int amount, struct s_fdf_settings *settings)
{
	t_xyz			start;
	t_xyz			stop;
	static int		width = 0;
	int				i;

	if (!width)
		width = get_map_width(0);
	i = -1;
	while (++i < amount)
	{
		save_coord(i, i + 1, 0);
		if ((i + 1) % width)
		{
			start = vertices[i];
			stop = vertices[i + 1];
			center_image(&start, &stop, 0, settings);
		}
		save_coord(i, i + width, 0);
		if (i + width < amount)
		{
			start = vertices[i];
			stop = vertices[i + width];
			center_image(&start, &stop, 0, settings);
		}
	}
}
