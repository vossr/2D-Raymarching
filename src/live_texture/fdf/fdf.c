/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/20 18:25:49 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_vertices(t_xyz angle, t_xyz *vertices, int amount)
{
	float	sin_angle;
	float	cos_angle;
	float	a;
	float	b;
	int		n;

	n = -1;
	while (++n < amount)
	{
		sin_angle = sin(angle.x);
		cos_angle = cos(angle.x);
		a = vertices[n].y;
		b = vertices[n].z;
		vertices[n].y = a * cos_angle - b * sin_angle;
		vertices[n].z = b * cos_angle + a * sin_angle;
		sin_angle = sin(angle.y);
		cos_angle = cos(angle.y);
		a = vertices[n].x;
		b = vertices[n].z;
		vertices[n].x = a * cos_angle + b * sin_angle;
		vertices[n].z = b * cos_angle - a * sin_angle;
	}
}

void	fdf_rotate(t_xyz *vertices, int amount, struct s_fdf_settings *settings)
{
	static t_xyz	angle = {.x = -0.5, .y = 0.5};

	if (settings->reset_b)
	{
		angle.x = -0.5;
		angle.y = 0.5;
		settings->reset_b = 0;
	}
	if (settings->spin_b)
		angle.y += 0.008;
	rotate_vertices(angle, vertices, amount);
}

void	render_layer(struct s_fdf_settings *settings)
{
	static t_xyz	*vertices_save = NULL;
	static t_xyz	*vertices = NULL;
	static int		amount = 0;
	int				i;

	if (!vertices_save)
	{
		vertices_save = make_map(NULL, NULL, NULL);
		amount = get_map_len(0);
		vertices = (t_xyz *)malloc(sizeof(t_xyz) * amount);
		if (!vertices)
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

void	fdf(void)
{
	static struct s_fdf_settings	settings;
	static int						first = 1;

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
	render_layer(&settings);
	cycle_colors(&settings.color);
}
