/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 19:52:10 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/06 11:08:21 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static unsigned char	**load_texture(int *line_s, int bps, int j)
{
	void			**mlx;
	char			*files[4];
	void			*texture[4];
	unsigned char	**data;
	int				endian;

	files[0] = "textures/stone.xpm";
	files[1] = "textures/redbrick.xpm";
	files[2] = "textures/bluewall.xpm";
	files[3] = "textures/door.xpm";
	data = (unsigned char**)malloc(sizeof(unsigned char*) * 4);
	mlx = get_mlx(NULL);
	j = -1;
	while (++j < 4)
	{
		texture[j] = mlx_xpm_file_to_image(mlx[0], files[j], &bps, line_s);
		data[j] = (unsigned char*)mlx_get_data_addr(texture[j], &bps,
											line_s, &endian);
	}
	return (data);
}

void					put_texture(int line_x, t_float_xy line,
							int texture_id, float texture_x)
{
	static unsigned char	**texture = NULL;
	int						y;
	int						tex_size;
	int						xd;
	int						yd;

	tex_size = 64;
	if (!texture)
		texture = load_texture(&y, 0, 0);
	y = -1;
	while (++y < line.x)
		pixel_put(line_x, y, 0x87ceeb);
	xd = (int)(tex_size * texture_x);
	if (xd == tex_size)
		xd--;
	while (y < line.y && y < WIN_HEIGHT)
	{
		yd = (int)(tex_size * (((float)y - line.x) / (line.y - line.x)));

		pixel_put(line_x, y,
				texture[texture_id][yd * (int)tex_size * 4 + xd * 4 + 2] * 0x10000 +
				texture[texture_id][yd * (int)tex_size * 4 + xd * 4 + 1] * 0x100 +
				texture[texture_id][yd * (int)tex_size * 4 + xd * 4 + 0]);
		y++;
	}
	y--;
	while (++y < WIN_HEIGHT)
		pixel_put(line_x, y, texture_id == 8 ? 0xFFFFE0 : 0x444444);
}
