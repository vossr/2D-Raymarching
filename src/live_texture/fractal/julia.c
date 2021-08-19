/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:40:28 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/19 02:41:35 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	julia_iter(PRECISION cx, PRECISION cy, int max_iter, t_position_xy pos)
{
	PRECISION	zx;
	PRECISION	zy;
	PRECISION	tempx;
	int			iteration;

	zx = 0;
	zy = 0;
	iteration = 0;
	zx = cx;
	zy = cy;
	cx = (3.0 / LIVE_TEXTURE_SIZE) * (pos.x - LIVE_TEXTURE_SIZE / 2);
	cy = (2.0 / LIVE_TEXTURE_SIZE) * (pos.y - LIVE_TEXTURE_SIZE / 2);
	while ((zx * zx + zy * zy < 4) && (iteration < max_iter))
	{
		tempx = zx * zx - zy * zy + cx;
		zy = 2 * zx * zy + cy;
		zx = tempx;
		iteration++;
	}
	return (iteration);
}

void	julia(t_f_settings *settings, int start, int stop)
{
	t_position_xy	pos;
	PRECISION		cx;
	PRECISION		cy;
	int				x;
	int				y;

	y = start;
	pos.x = settings->pos.x + LIVE_TEXTURE_SIZE;
	pos.y = settings->pos.y + LIVE_TEXTURE_SIZE;
	while (y < stop)
	{
		x = 0;
		while (x < LIVE_TEXTURE_SIZE)
		{
			cx = (x - LIVE_TEXTURE_SIZE / 2)
				* ((settings->zoom) / LIVE_TEXTURE_SIZE);
			cy = (y - LIVE_TEXTURE_SIZE / 2)
				* ((settings->zoom) / LIVE_TEXTURE_SIZE);
			live_pixel_put(select_color(settings->color, settings->max_iter,
					settings->frame,
					julia_iter(cx, cy, settings->max_iter, pos)), x, y, NULL);
			x++;
		}
		y++;
	}
}
