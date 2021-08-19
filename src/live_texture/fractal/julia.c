/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:40:28 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/19 20:49:52 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	get_fire_color(int max, int frame_id, int iter)
{
	static int		other2 = 0;
	static int		wait_i = 1;
	static int		wait_time = 0;
	static float	fire_amount = 0;

	if (other2 != frame_id && (wait_i++ + 1))
		other2 = frame_id;
	if (wait_i > wait_time)
	{
		wait_time = rand() % 10;
		fire_amount = (float)(rand() % 100) / 100 + 1;
		if (rand() % 3 < 3)
			fire_amount = fire_amount + 1.5;
		wait_i = 0;
	}
	if (iter == max)
		return (0xFFFFFF);
	else if (iter < max / fire_amount)
	{
		max /= fire_amount;
		return ((int)(0xFF - 0xFF * ((float)(max - iter) / max)) << 16);
	}
	iter /= fire_amount;
	max /= fire_amount;
	return ((0xFF0000) + ((int)(0xFF * ((float)iter / max)) << 8));
}

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
			live_pixel_put(get_fire_color(settings->max_iter,
					settings->frame,
					julia_iter(cx, cy, settings->max_iter, pos)), x, y, NULL);
			x++;
		}
		y++;
	}
}
