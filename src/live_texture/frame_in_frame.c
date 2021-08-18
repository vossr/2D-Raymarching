/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_in_frame.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 01:31:07 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/19 02:01:04 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "live_texture.h"

static int	frame_in_frame_get_pixel(int x, int y)
{
	static unsigned char	*data = NULL;
	static t_int_xy			wins;
	void					**mlx;
	int						n;

	if (!data)
	{
		mlx = get_mlx(NULL);
		data = (unsigned char *)mlx_get_data_addr(mlx[2], &wins.y, &wins.x, &n);
		n = wins.x;
		wins = get_window_size();
		wins.x = n;
	}
	n = 0;
	n += data[(y * wins.x) + (x * 4) + 3] << 8 * 3;
	n += data[(y * wins.x) + (x * 4) + 2] << 8 * 2;
	n += data[(y * wins.x) + (x * 4) + 1] << 8 * 1;
	n += data[(y * wins.x) + (x * 4) + 0] << 8 * 0;
	return (n);
}

void	frame_in_frame(void)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < LIVE_TEXTURE_SIZE)
	{
		x = 0;
		while (x < LIVE_TEXTURE_SIZE)
		{
			if (!x || !y
				|| x == LIVE_TEXTURE_SIZE - 1 || y == LIVE_TEXTURE_SIZE - 1)
				color = 0xff0000;
			else
				color = frame_in_frame_get_pixel(WIN_WIDTH
						* ((float)x / LIVE_TEXTURE_SIZE),
						WIN_HEIGHT * ((float)y / LIVE_TEXTURE_SIZE));
			live_pixel_put(color, x, y, NULL);
			x++;
		}
		y++;
	}
}
