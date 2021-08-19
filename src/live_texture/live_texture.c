/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 23:09:47 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/19 03:40:10 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "live_texture.h"
#include "fractal.h"
#include "fdf.h"

void	live_pixel_put(int color, int x, int y,
							unsigned int **get_textures)
{
	static unsigned int	**textures;
	static int			id;

	if (get_textures)
	{
		textures = get_textures;
		return ;
	}
	if (x == -1)
	{
		id = color;
		return ;
	}
	if (x >= 0 && y >= 0 && x < LIVE_TEXTURE_SIZE
		&& y < LIVE_TEXTURE_SIZE)
		textures[id][x + LIVE_TEXTURE_SIZE * y] = color;
}

void	init_live_texture(unsigned int **textures)
{
	int	i;

	i = 4;
	while (i < 8)
	{
		textures[i] = (unsigned int *)malloc(sizeof(unsigned int)
				* LIVE_TEXTURE_SIZE * LIVE_TEXTURE_SIZE);
		i++;
	}
	live_pixel_put(0, 0, 0, textures);
	init_fractal();
	init_fdf();
}

void	minimap_player(t_settings *settings)
{
	int	x;
	int	y;

	y = -4;
	while (y < 5)
	{
		x = -4;
		while (x < 5)
		{
			live_pixel_put(0xaadaff, x + (int)(LIVE_TEXTURE_SIZE
					* (settings->location.x / settings->map_width)),
				y + (int)(LIVE_TEXTURE_SIZE
					* (settings->location.y / settings->map_height)), NULL);
			x++;
		}
		y++;
	}
}

static void	minimap(t_settings *settings)
{
	int	x;
	int	y;
	int	mapx;
	int	mapy;

	y = 0;
	while (y < LIVE_TEXTURE_SIZE)
	{
		x = -1;
		while (++x < LIVE_TEXTURE_SIZE)
		{
			mapy = settings->map_height
				* ((float)y / LIVE_TEXTURE_SIZE);
			mapx = settings->map_width
				* ((float)x / LIVE_TEXTURE_SIZE);
			if (settings->map[mapy][mapx] == 1)
				live_pixel_put(0xfff2af, x, y, NULL);
			else if (settings->map[mapy][mapx] == 2)
				live_pixel_put(0xc3ecb2, x, y, NULL);
			else
				live_pixel_put(0xe8e8e8, x, y, NULL);
		}
		y++;
	}
	minimap_player(settings);
}

void	live_texture(t_settings *settings)
{
	int	x;
	int	y;

	live_pixel_put(4, -1, 0, NULL);
	frame_in_frame();
	live_pixel_put(5, -1, 0, NULL);
	minimap(settings);
	live_pixel_put(6, -1, 0, NULL);
	fractal();
	live_pixel_put(7, -1, 0, NULL);
	y = 0;
	while (y < LIVE_TEXTURE_SIZE)
	{
		x = 0;
		while (x < LIVE_TEXTURE_SIZE)
		{
			live_pixel_put(0, x, y, NULL);
			x++;
		}
		y++;
	}
	fdf();
}
