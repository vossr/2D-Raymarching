/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 17:47:00 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	make_gradient(int **res)
{
	double	red;
	double	grn;
	double	blu;
	int	i;

	i = 0;
	res[0] = (int*)malloc(sizeof(int) * (310 * 310));
	while (i < 310)
	{
		red = sin(0.02 * i + 0) * 127 + 128;
		grn = sin(0.02 * i + 2) * 127 + 128;
		blu = sin(0.02 * i + 4) * 127 + 128;
		for (int y = 0; y < 310; y++)
			res[0][(i * 310) + y] = ((int)red * 65536 + (int)grn * 256 + (int)blu);
		i++;
	}
	return ;
}

int		set_gradient_color(int x, int y)
{
	double	red;
	double	grn;
	double	blu;
	int		i;

	i = 0;
	while (i < 310)
	{
		red = sin(0.02 * i + 0) * 127 + 128;
		grn = sin(0.02 * i + 2) * 127 + 128;
		blu = sin(0.02 * i + 4) * 127 + 128;
		if (i == x && y < 450 && y > 30)
			return ((int)red * 65536 + (int)grn * 256 + (int)blu);
		i++;
	}
	return (0);
}
/*
int		gradient(struct s_fdf_settings *settings)
{
	(void)settings;
	static int	*gradient_img = NULL;
	int		i;
	//t_int_xy	cursor;

	if (!gradient_img)
		make_gradient(&gradient_img);
	i = 1;
	while (i < 310 * 310)
	{
		live_pixel_put(i / 310, i % 310 + 31, gradient_img[i]);
		i++;
	}
	if (is_mouse_down(1))
	{
		cursor = get_cursor();
		if ((cursor.x >= 0 && cursor.x < 311) && (cursor.y < 341 && cursor.y > 30))
		{
			settings->color.x = set_gradient_color(cursor.x, cursor.y);
			settings->color.y = set_gradient_color(cursor.x, cursor.y);
		}
	}
	/
	return (1);
}
*/
void	cycle_colors(t_xyz *color)
{
	static int	i = 0;
	static int	old = 0;
	double		red;
	double		grn;
	double		blu;

	if (color->x != old && color->x != 0xFFFFFF)
		while (color->x != old)
		{
			if (i > 310)
				i = 0;
			red = sin(0.02 * i + 0) * 127 + 128;
			grn = sin(0.02 * i + 2) * 127 + 128;
			blu = sin(0.02 * i + 4) * 127 + 128;
			old = ((int)red * 65536 + (int)grn * 256 + (int)blu);
			i++;
		}
	i = i > 310 ? 0 : i;
	red = sin(0.02 * i + 0) * 127 + 128;
	grn = sin(0.02 * i + 2) * 127 + 128;
	blu = sin(0.02 * i + 4) * 127 + 128;
	old = ((int)red * 65536 + (int)grn * 256 + (int)blu);
	color->x = old;
	color->y = old;
	i += 1;
}
