/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 19:52:10 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 07:35:09 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static unsigned int	**load_texture(int *w, int bps, int j)
{
	void			**mlx;
	char			*files[4];
	void			*txtur[4];
	unsigned char	**data;
	int				endi;

	files[0] = "textures/stone.xpm";
	files[1] = "textures/redbrick.xpm";
	files[2] = "textures/bluewall.xpm";
	files[3] = "textures/door.xpm";
	data = (unsigned char **)malloc(sizeof(unsigned char *) * 4);
	if (!data)
		fatal_error("memory allocation failed");
	mlx = get_mlx(NULL);
	j = -1;
	while (++j < 4)
	{
		txtur[j] = mlx_xpm_file_to_image(mlx[0], files[j], &bps, w);
		data[j] = (unsigned char *)mlx_get_data_addr(txtur[j], &bps, w, &endi);
	}
	*w /= 4;
	return ((unsigned int **)data);
}

static void	render(int line_x, t_float_xy line,
							int texture_id, float texture_x)
{
	static unsigned int		**texture = NULL;
	static int				tex_size;
	int						y;
	int						xd;
	int						yd;

	if (!texture)
		texture = load_texture(&tex_size, 0, 0);
	y = -1;
	while (++y < line.x)
		pixel_put(line_x, y, 0x87ceeb);
	xd = (int)(tex_size * texture_x);
	if (xd == tex_size)
		xd--;
	while (y < line.y && y < WIN_HEIGHT)
	{
		yd = (int)(tex_size * (((float)y - line.x) / (line.y - line.x)));
		pixel_put(line_x, y, texture[texture_id][yd * tex_size + xd]);
		y++;
	}
	y--;
	while (++y < WIN_HEIGHT)
		pixel_put(line_x, y, 0x444444);
}

static void	texture_x(t_float_xy step, t_float_xy cast, int *wall, float *tex_x)
{
	if ((int)cast.x != (int)(cast.x - step.x) &&
			(int)cast.y != (int)(cast.y - step.y))
		return ;
	if ((int)cast.x < (int)(cast.x - step.x))
	{
		*wall = 0;
		*tex_x = 1.0 - (cast.y - (int)cast.y);
	}
	else if ((int)cast.y < (int)(cast.y - step.y))
	{
		*wall = 1;
		*tex_x = cast.x - (int)cast.x;
	}
	else if ((int)cast.y > (int)(cast.y - step.y))
	{
		*wall = 2;
		*tex_x = 1.0 - (cast.x - (int)cast.x);
	}
	else
	{
		*wall = 3;
		*tex_x = cast.y - (int)cast.y;
	}
}

static void	texture_mapper(t_float_xy step, t_float_xy cast,
											int x, t_settings *settings)
{
	static int		wall_dir = 0;
	static float	tex_x = 0;
	t_float_xy		line;
	float			dist;

	texture_x(step, cast, &wall_dir, &tex_x);
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
