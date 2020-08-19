/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 19:52:10 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/16 20:03:21 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#define TEX_SIZE 64

int		read_texture(int id, int y, int x)
{
	static void **mlx = NULL;
	char		filename[4][40] = {"textures/stone.xpm", "textures/redbrick.xpm", "textures/bluewall.xpm", "textures/door.xpm"};
	void	*texture[4];
	static unsigned char	*data[4];
	static int			bps, line_s, endian;

	if (!mlx)
	{
		mlx = get_mlx(NULL);
		for (int j = 0; j < 4; j++)
		{
			texture[j] = mlx_xpm_file_to_image(mlx[0], filename[j], &bps, &line_s);
			data[j] = (unsigned char*)mlx_get_data_addr(texture[j], &bps, &line_s, &endian);
		}
	}
	return (data[id][y * line_s + x * 4 + 2] * 0x10000 +
	data[id][y * line_s + x * 4 + 1] * 0x100 + data[id][y * line_s + x * 4 + 0]);
}

void	megapixel_put(int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			pixel_put(x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	map_print(t_float_xy location, t_int_xy map_size, int **map)
{
	int			x;
	int			y;

	y = 0;
	while (y < map_size.y)
	{
		x = 0;
		while (x < map_size.x)
		{
			if (map[y][x] == 1)
				megapixel_put(x * 8, y * 8, 0xFFFFFF);
			else
				megapixel_put(x * 8, y * 8, 0);
			x++;
		}
		y++;
	}
	location.x *= 8;
	location.y *= 8;
	megapixel_put((int)location.x - 4, (int)location.y - 4, 0xFF00);
}

void	put_texture(int line_x, t_float_xy line,
					int texture_id, float texture_x)
{
	int			y;

	y = 0;
	while (y < line.x)
	{
		pixel_put(line_x, y, 0x7777FF);
		y++;
	}
	y = line.x;
	while (y < line.y)
	{
		pixel_put(line_x, y, read_texture(texture_id, (int)(TEX_SIZE * (((float)y
			- line.x) / (line.y - line.x))), (int)(TEX_SIZE * texture_x)));
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		pixel_put(line_x, y, 0x444444);
		y++;
	}
}
