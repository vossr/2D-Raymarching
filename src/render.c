/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 19:52:10 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/19 00:57:52 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "live_texture.h"

static unsigned int	**load_texture(int *w, int bps, int j)
{
	char			*files[4];
	void			*txtur[4];
	unsigned int	**data;
	int				endi;

	files[0] = "textures/stone.xpm";
	files[1] = "textures/redbrick.xpm";
	files[2] = "textures/bluewall.xpm";
	files[3] = "textures/door.xpm";
	data = (unsigned int **)malloc(sizeof(unsigned int *));
	if (!data)
		fatal_error("memory allocation failed");
	j = -1;
	while (++j < 4)
	{
		txtur[j] = NULL;
		txtur[j] = mlx_xpm_file_to_image(*get_mlx(NULL), files[j], &bps, w);
		if (!txtur[j])
			fatal_error("texture file not found");
		data[j] = (unsigned int *)mlx_get_data_addr(txtur[j], &bps, w, &endi);
	}
	w[0] /= 4;
	w[1] = LIVE_TEXTURE_SIZE;
	init_live_texture(data);
	return (data);
}

static void	render(int line_x, t_vec2 line,
							int texture_id, float texture_x)
{
	static unsigned int		**texture = NULL;
	static int				tex_size[3];
	int						y;
	int						xd;
	int						yd;

	if (!texture)
		texture = load_texture(&tex_size[0], 0, 0);
	tex_size[2] = tex_size[texture_id > 3];
	y = -1;
	while (++y < line.x)
		pixel_put(line_x, y, 0x87ceeb);
	xd = (int)(tex_size[2] * texture_x);
	if (xd == tex_size[2])
		xd--;
	while (y < line.y && y < WIN_HEIGHT)
	{
		yd = (int)(tex_size[2] * (((double)y - line.x) / (line.y - line.x)));
		pixel_put(line_x, y, texture[texture_id][yd * tex_size[2] + xd]);
		y++;
	}
	y--;
	while (++y < WIN_HEIGHT)
		pixel_put(line_x, y, 0x444444);
}

static void	texture_x(t_vec2 step, t_vec2 cast, int *wall, double *tex_x)
{
	if ((int)cast.x != (int)(cast.x - step.x) &&
			(int)cast.y != (int)(cast.y - step.y))
		return ;
	if ((int)cast.x < (int)(cast.x - step.x))
	{
		*wall += 0;
		*tex_x = 1.0 - (cast.y - (int)cast.y);
	}
	else if ((int)cast.y < (int)(cast.y - step.y))
	{
		*wall += 1;
		*tex_x = cast.x - (int)cast.x;
	}
	else if ((int)cast.y > (int)(cast.y - step.y))
	{
		*wall += 2;
		*tex_x = 1.0 - (cast.x - (int)cast.x);
	}
	else
	{
		*wall += 3;
		*tex_x = cast.y - (int)cast.y;
	}
}

static void	texture_mapper(t_vec2 step, t_vec2 cast,
											int x, t_settings *settings)
{
	static int		wall_dir = 0;
	static double	tex_x = 0;
	t_vec2			line;
	double			dist;

	wall_dir = (settings->map[(int)cast.y][(int)cast.x] - 1) * 4;
	texture_x(step, cast, &wall_dir, &tex_x);
	cast.x -= settings->location.x;
	cast.y -= settings->location.y;
	dist = sqrt(cast.x * cast.x + cast.y * cast.y);
	dist *= cos(deg_to_rad(settings->ray_angle - settings->angle));
	line.x = WIN_HEIGHT / 2 - WIN_HEIGHT / 2 / dist;
	line.y = WIN_HEIGHT / 2 + WIN_HEIGHT / 2 / dist;
	render(WIN_WIDTH - 1 - x, line, wall_dir, tex_x);
}

void	raycast(t_settings *settings)
{
	int		x;
	t_vec2	cast;
	t_vec2	step;

	settings->ray_angle = settings->angle - FOV / 2;
	x = 0;
	while (x < WIN_WIDTH)
	{
		step.x = sin(deg_to_rad(settings->ray_angle)) * STEP_LEN;
		step.y = cos(deg_to_rad(settings->ray_angle)) * STEP_LEN;
		cast = settings->location;
		while (settings->map[(int)cast.y][(int)cast.x] == 0)
		{
			cast.x += step.x;
			cast.y += step.y;
		}
		texture_mapper(step, cast, x, settings);
		settings->ray_angle += FOV / WIN_WIDTH;
		x++;
	}
}
