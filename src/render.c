/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 19:52:10 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/20 13:48:35 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static unsigned char	**load_texture(int *line_s, int bps, int j)
{
	void			**mlx;
	char			*files[9];
	void			*texture[9];
	unsigned char	**data;
	int				endian;

	files[0] = "textures/stone.xpm";
	files[1] = "textures/redbrick.xpm";
	files[2] = "textures/bluewall.xpm";
	files[3] = "textures/door.xpm";
	files[4] = "textures/painting.xpm";
	files[5] = "textures/achtung.xpm";
	files[6] = "textures/flag.xpm";
	files[7] = "textures/eagle.xpm";
	files[8] = "textures/sandstone.xpm";
	data = (unsigned char**)malloc(sizeof(unsigned char*) * 9);
	mlx = get_mlx(NULL);
	j = 0;
	while (j < 9)
	{
		texture[j] = mlx_xpm_file_to_image(mlx[0], files[j], &bps, line_s);
		data[j] = (unsigned char*)mlx_get_data_addr(texture[j], &bps, line_s, &endian);
		j++;
	}
	return (data);
}

void			megapixel_put(int x, int y, int color)
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

void			map_print(t_settings *settings)
{
	int			x;
	int			y;

	y = 0;
	while (y < settings->map_size.y)
	{
		x = 0;
		while (x < settings->map_size.x)
		{
			if (settings->map[y][x] == 1 || settings->map[y][x] == 2)
				megapixel_put(x * 8, y * 8, 0xFFFFFF);
			else
				megapixel_put(x * 8, y * 8, 0);
			x++;
		}
		y++;
	}
	t_float_xy location2;
	location2.x = settings->location.x * 8;
	location2.y = settings->location.y * 8;
	megapixel_put((int)location2.x - 4, (int)location2.y - 4, 0xFF00);
}

void			put_texture(int line_x, t_float_xy line,
					int texture_id, float texture_x)
{
	static unsigned char	**texture = NULL;
	int						line_s;
	int						y;
	float					tex_size;

	if (!texture)
		texture = load_texture(&line_s, 0, 0);
	tex_size = 64.0;
	line_s = 256;
	if (texture_id > 7)
	{
		texture_id = 8;
		tex_size = 512.0;
		line_s = 2024;
	}
	y = 0;
	while (y < line.x)
	{
		pixel_put(line_x, y, 0x87ceeb);
		y++;
	}
	y = line.x;
	if (y < 0)
		y = 0;
	int xd = (int)(tex_size * texture_x);
	int yd;
	while (y < line.y && y < WIN_HEIGHT)
	{
		yd = (int)(tex_size * (((float)y - line.x) / (line.y - line.x)));
		pixel_put(line_x, y, texture[texture_id][yd * line_s + xd * 4 + 2] * 0x10000 +
				texture[texture_id][yd * line_s + xd * 4 + 1] * 0x100 + texture[texture_id][yd * line_s + xd * 4 + 0]);
		y++;
	}
	y--;
	while (++y < WIN_HEIGHT)
		pixel_put(line_x, y, 0x444444);
}
