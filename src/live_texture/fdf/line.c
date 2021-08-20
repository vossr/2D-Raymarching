/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:19:28 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/20 17:37:00 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_abs(double n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

unsigned int	make_fade(unsigned int color1, unsigned int color2,
									unsigned int fade)
{
	unsigned char	*rgb1;
	unsigned char	*rgb2;
	unsigned int	newr;
	unsigned int	newg;
	unsigned int	newb;

	rgb1 = (unsigned char *)&color1;
	rgb2 = (unsigned char *)&color2;
	newr = (rgb1[2] * (0xff - fade) + rgb2[2] * fade) / 0xff;
	newg = (rgb1[1] * (0xff - fade) + rgb2[1] * fade) / 0xff;
	newb = (rgb1[0] * (0xff - fade) + rgb2[0] * fade) / 0xff;
	return ((newr << 8 * 2) + (newg << 8 * 1) + (newb << 8 * 0) + 0);
}

void	print_line(t_xyz start, t_xyz stop,
			unsigned int color1, unsigned int color2)
{
	t_xyz			step;
	t_xyz			pos;
	int				i;

	if (start.z < 0 || stop.z < 0)
		return ;
	i = 0;
	pos.x = start.x;
	pos.y = start.y;
	pos.z = 0;
	step.z = ft_abs(stop.y - start.y);
	if (ft_abs(stop.x - start.x) > ft_abs(stop.y - start.y))
		step.z = ft_abs(stop.x - start.x);
	step.x = (stop.x - start.x) / (float)step.z;
	step.y = (stop.y - start.y) / (float)step.z;
	while (pos.z <= step.z && i < 1000)
	{
		live_pixel_put(make_fade(color1, color2,
				0xff * ((pos.z) / (step.z))), pos.x, pos.y, NULL);
		pos.x += step.x;
		pos.y += step.y;
		pos.z++;
		i++;
	}
}
