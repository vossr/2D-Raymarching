/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 19:52:10 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/06 15:34:38 by rpehkone         ###   ########.fr       */
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

static void				render(int line_x, t_float_xy line,
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

static void	texture_x_pos(t_float_xy direction, t_float_xy cast,
									int *wall_dir, float *texture_x)
{
	if ((int)cast.x != (int)(cast.x - direction.x) &&
				(int)cast.y != (int)(cast.y - direction.y))
	{
		return ;
	}
	else if ((int)cast.x < (int)(cast.x - direction.x))
	{
		*wall_dir = 0;
		*texture_x = 1.0 - (cast.y - (int)cast.y);
	}
	else if ((int)cast.y < (int)(cast.y - direction.y))
	{
		*wall_dir = 1;
		*texture_x = cast.x - (int)cast.x;
	}
	else if ((int)cast.y > (int)(cast.y - direction.y))
	{
		*wall_dir = 2;
		*texture_x = 1.0 - (cast.x - (int)cast.x);
	}
	else
	{
		*wall_dir = 3;
		*texture_x = cast.y - (int)cast.y;
	}
}

void	texture_mapper(t_float_xy step, t_float_xy cast, int x, t_settings *settings)
{
	static int		wall_dir = 0;
	static float	tex_x = 0;
	t_float_xy		line;
	float			dist;

	texture_x_pos(step, cast, &wall_dir, &tex_x);
	cast.x -= settings->location.x;
	cast.y -= settings->location.y;
	dist = sqrtf(cast.x * cast.x + cast.y * cast.y);
	dist *= cosf(deg_to_rad(settings->ray_angle - settings->angle));
	line.x = WIN_HEIGHT / 2 - WIN_HEIGHT / 2 / dist;
	line.y = WIN_HEIGHT / 2 + WIN_HEIGHT / 2 / dist;
	render(WIN_WIDTH - 1 - x, line, wall_dir, tex_x);
}

void	raycast(t_settings *settings)
{
	int				x;
	t_float_xy		cast;
	t_float_xy		step;

	settings->ray_angle = settings->angle - FOV / 2;
	x = 0;
	while (x < WIN_WIDTH)
	{
		step.x = sinf(deg_to_rad(settings->ray_angle)) / RAY_PREC;
		step.y = cosf(deg_to_rad(settings->ray_angle)) / RAY_PREC;
		cast = settings->location;
		while (settings->map[(int)cast.y][(int)cast.x] != 1)
		{
			cast.x += step.x;
			cast.y += step.y;
		}
		texture_mapper(step, cast, x, settings);
		settings->ray_angle += FOV / WIN_WIDTH;
		x++;
	}
}
