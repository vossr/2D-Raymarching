/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/20 18:37:46 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	set_gradient_color(int x, int y)
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

void	cycle_colors(t_xyz *color)
{
	static int	i = 0;
	static int	old = 0;
	double		red;
	double		grn;
	double		blu;

	while (color->x != old && color->x != 0xFFFFFF
		&& color->x != old)
	{
		if (i > 310)
			i = 0;
		red = sin(0.02 * i + 0) * 127 + 128;
		grn = sin(0.02 * i + 2) * 127 + 128;
		blu = sin(0.02 * i + 4) * 127 + 128;
		old = ((int)red * 65536 + (int)grn * 256 + (int)blu);
		i++;
	}
	if (++i > 310)
		i = 0;
	red = sin(0.02 * i + 0) * 127 + 128;
	grn = sin(0.02 * i + 2) * 127 + 128;
	blu = sin(0.02 * i + 4) * 127 + 128;
	old = ((int)red * 65536 + (int)grn * 256 + (int)blu);
	color->x = old;
	color->y = old;
}
