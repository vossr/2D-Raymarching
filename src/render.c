/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 19:52:10 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/19 20:43:17 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#define TEX_SIZE 64

unsigned char	**load_texture(int *line_s)
{
	void **mlx = NULL;
	char		filename[8][40] = {"textures/stone.xpm", "textures/redbrick.xpm", "textures/bluewall.xpm", "textures/door.xpm", "textures/painting.xpm", "textures/achtung.xpm", "textures/flag.xpm", "textures/eagle.xpm"};
	void	*texture[8];
	unsigned char	**data;
	int			bps, endian;

	data = (unsigned char**)malloc(sizeof(unsigned char*) * 8);
	mlx = get_mlx(NULL);
	for (int j = 0; j < 8; j++)
	{
		texture[j] = mlx_xpm_file_to_image(mlx[0], filename[j], &bps, line_s);
		data[j] = (unsigned char*)mlx_get_data_addr(texture[j], &bps, line_s, &endian);
	}
	return (data);
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
			if (map[y][x] != 0)
				megapixel_put(x * 8, y * 8, 0xFFFFFF);
			else
				megapixel_put(x * 8, y * 8, 0);
			x++;
		}
		y++;
	}
	location.x *= 8;
	location.y *= 8;
	megapixel_put((int)location.y - 4, (int)location.x - 4, 0xFF00);
}

void	put_texture(int line_x, t_float_xy line,
					int texture_id, float texture_x)
{
	static unsigned char	**texture = NULL;
	static int				line_s;
	int						y;

	if (!texture)
		texture = load_texture(&line_s);
	y = 0;
	while (y < line.x)
	{
		pixel_put(line_x, y, 0x87ceeb);
		y++;
	}
	y = line.x;
	if (y < 0)
		y = 0;
	while (y < line.y && y < WIN_HEIGHT)
	{
		int xd = (int)(TEX_SIZE * texture_x);
		int yd = (int)(TEX_SIZE * (((float)y - line.x) / (line.y - line.x)));
		pixel_put(line_x, y, texture[texture_id][yd * line_s + xd * 4 + 2] * 0x10000 +
				texture[texture_id][yd * line_s + xd * 4 + 1] * 0x100 + texture[texture_id][yd * line_s + xd * 4 + 0]);
		y++;
	}
	y--;
	while (++y < WIN_HEIGHT)
		pixel_put(line_x, y, 0x444444);
}
