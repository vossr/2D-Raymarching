/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 18:37:25 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_vertices(float angle, t_xyz *vertices, int amount, int axis_x)
{
	float	sin_angle;
	float	cos_angle;
	float	a;
	float	b;
	int		n;

	n = -1;
	sin_angle = sin(angle);
	cos_angle = cos(angle);
	while (++n < amount)
		if (axis_x)
		{
			a = vertices[n].y;
			b = vertices[n].z;
			vertices[n].y = a * cos_angle - b * sin_angle;
			vertices[n].z = b * cos_angle + a * sin_angle;
		}
		else
		{
			a = vertices[n].x;
			b = vertices[n].z;
			vertices[n].x = a * cos_angle + b * sin_angle;
			vertices[n].z = b * cos_angle - a * sin_angle;
		}
}

void	fdf_rotate(t_xyz *vertices, int amount, struct s_fdf_settings *settings)
{
	static float	x = 0.5;
	//static float	x2 = 0;
	static float	y = 0.5;
	//static float	y2 = 0;
	//t_int_xy	cursor;

	if (settings->reset_b)
	{
		x = 0.5;
		y = 0.5;
		settings->reset_b = 0;
	}
	//cursor = get_cursor();
	if (settings->spin_b)
		y += 0.008;
	/*
	if (!settings->active_layer && is_mouse_down(1))
	{
		x -= (cursor.y - y2) * 0.01;
		y -= (cursor.x - x2) * 0.01;
	}
	x2 = cursor.x;
	y2 = cursor.y;
	*/
	rotate_vertices(-1 * x, vertices, amount, 1);
	rotate_vertices(y, vertices, amount, 0);
}

void		render_layer(struct s_fdf_settings *settings)
{
	static t_xyz	*vertices_save = NULL;
	static t_xyz	*vertices = NULL;
	static int		amount = 0;
	int		i;

	if (!vertices_save)
	{
		vertices_save = make_map(NULL, NULL, NULL);
		amount = get_map_len(0);
		if (!(vertices = (t_xyz*)malloc(sizeof(t_xyz) * amount)))
			ft_error();
	}
	i = 0;
	while (i < amount)
	{
		vertices[i].x = vertices_save[i].x;
		vertices[i].y = vertices_save[i].y;
		vertices[i].z = vertices_save[i].z * settings->height;
		i++;
	}
	fdf_rotate(vertices, amount, settings);
	draw(vertices, amount, settings);
}

/*
	unsigned	projection_b : 1;
	unsigned	fov_b : 1;
	float		fov;
	unsigned	spin_b : 1;
	unsigned	color_b : 1;
	struct s_xyz	color;
	unsigned	cycle_b : 1;
	unsigned	height_b : 1;
	float		height;
	unsigned	height_color_b : 1;
	unsigned	fps_b : 1;
	unsigned	reset_b : 1;
	unsigned	active_layer : 1;
*/

void		fdf(void)
{
	static struct s_fdf_settings	settings;
	static int			first = 1;

	//if (is_key_down(53))
	//	exit(0);
	//else if (first)
	if (first)
	{
		ft_bzero(&settings, sizeof(settings));
		settings.fov = -1;
		settings.color.x = 0xFFFFFF;
		settings.color.y = 0xFFFFFF;
		settings.height = 1;
		settings.cycle_b = 1;
		settings.projection_b = 1;
		settings.height_color_b = 1;
		settings.spin_b = 1;
		first = 0;
	}
	//update_image();
	render_layer(&settings);
	//button_layer(&settings);
	cycle_colors(&settings.color);;
	//text_layer(&settings);
}
