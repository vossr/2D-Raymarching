/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:44:10 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 21:39:06 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_perspective(struct s_fdf_settings *settings, t_xyz *start, t_xyz *stop)
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
	//if (set == -2)
	//	cycle_colors(&color);
	else if (set)
	{
		color.x = set;
		color.y = set;
	}
	//if (get_settings(7, NULL))
	//	return (add_color_height(color));
	return (color);
}

#include <stdio.h>
void	move_center(t_xyz *start, t_xyz *stop, struct s_fdf_settings *settings)
{
	static double	zoom = -1200;
	static int		w_move = 0;
	static int		h_move = 0;

	//if (is_mouse_down(4))
	//	zoom += 0.07;
	//if (is_mouse_down(5))
	//	zoom -= 0.07;
	zoom = zoom > 600 ? 600 : zoom;
	zoom = zoom < -4000 ? -4000 : zoom;
	start->z -= zoom;
	stop->z -= zoom;
	if (settings->projection_b)
		add_perspective(settings, start, stop);
	w_move = w_move ? w_move : 512 / 2;//get_width(NULL) / 2;
	h_move = h_move ? h_move : 512 / 2;//get_height(NULL) / 2 + 30;
	start->x += w_move;
	start->y += h_move;
	stop->x += w_move;
	stop->y += h_move;
	if (settings->height_color_b)
		print_line(*start, *stop, add_color_height(settings->color));
	else
		print_line(*start, *stop, settings->color);
	//printf("z = %lf\n", zoom);
}

void	center_image(t_xyz *start, t_xyz *stop, int reset, struct s_fdf_settings *settings)
{
	static int	x = 0;
	static int	y = 0;
	//static int	coordx = 0;
	//static int	coordy = 0;
	//t_int_xy	cursor;

	if (reset)
	{
		x = 0;
		y = 0;
		return ;
	}
	//cursor = get_cursor();
	//if (is_mouse_down(3))
		//x -= coordx - cursor.x;
	//if (is_mouse_down(3))
		//y -= coordy - cursor.y;
	//coordx = cursor.x;
	//coordy = cursor.y;
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
