/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:19:28 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 19:02:17 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_abs(double n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

unsigned	make_fade(t_xyz color, unsigned fade, signed xred)
{
	signed xgrn;
	signed xblu;
	signed yred;
	signed ygrn;
	signed yblu;

	if (color.x == color.y)
		return ((signed)color.x);
	xred = (((signed)color.x % 0x1000000) >> 4 * 4) - fade;
	xgrn = (((signed)color.x % 0x10000) >> 4 * 2) - fade;
	xblu = ((signed)color.x % 0x100) - fade;
	yred = (((signed)color.y % 0x1000000) >> 4 * 4);
	ygrn = (((signed)color.y % 0x10000) >> 4 * 2);
	yblu = ((signed)color.y % 0x100);
	yred = (signed)(((double)fade / 0xFF) * yred);
	ygrn = (signed)(((double)fade / 0xFF) * ygrn);
	yblu = (signed)(((double)fade / 0xFF) * yblu);
	xred = xred < 0 ? 0 : xred;
	xgrn = xgrn < 0 ? 0 : xgrn;
	xblu = xblu < 0 ? 0 : xblu;
	yred = yred > 0xFF ? 0xFF : yred;
	ygrn = ygrn > 0xFF ? 0xFF : ygrn;
	yblu = yblu > 0xFF ? 0xFF : yblu;
	return ((xred << 4 * 4) + (xgrn << 4 * 2) + xblu +
			(yred << 4 * 4) + (ygrn << 4 * 2) + yblu);
}

void	print_line(t_xyz start, t_xyz stop, t_xyz color)
{
	t_xyz	step;
	t_xyz	pos;
	int		i;

	if (start.z < 0 || stop.z < 0)
		return ;
	i = 0;
	pos.x = start.x;
	pos.y = start.y;
	pos.z = 0;
	step.z = ft_abs(stop.x - start.x) > ft_abs(stop.y - start.y) ?
			ft_abs(stop.x - start.x) : ft_abs(stop.y - start.y);
	step.x = (stop.x - start.x) / (float)step.z;
	step.y = (stop.y - start.y) / (float)step.z;
	while (pos.z <= step.z && i < 1000)
	{
		live_pixel_put(8, pos.x, pos.y, make_fade(color, 0xFF * ((pos.z) / (step.z)), 0));
		pos.x += step.x;
		pos.y += step.y;
		pos.z++;
		i++;
	}
}
