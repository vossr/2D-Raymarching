/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 19:47:35 by rpehkone          #+#    #+#             */
/*   Updated: 2020/09/30 15:50:21 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	put_sprite(int x, int x_offset, t_float_xy line)
{
	void					*guard = NULL;
	static unsigned char	*guard_data = NULL;
	static int				line_s;
	int						bps;
	int						endian;
	void					**mlx;

	if (!guard_data)
	{
		mlx = get_mlx(NULL);
		//check widht and height
		guard = mlx_xpm_file_to_image(mlx[0],
				"textures/guard.xpm", &bps, &line_s);
		if (guard == NULL)
			fatal_error("guard load fail");
		guard_data = (unsigned char*)mlx_get_data_addr(guard, &bps,
												&line_s, &endian);
	}
	//int a = x;
	int max = line.y - line.x;
	int start = line.x;
	while (line.x < line.y)
	{
		int a = 450 * ((line.x - start) / max);
		int b = x_offset;
		if (!guard_data[a * (int)(360 * 4) + b * 4 + 3])
			pixel_put(x, line.x,
			guard_data[a * (int)(360 * 4) + b * 4 + 2] * 0x10000 +
			guard_data[a * (int)(360 * 4) + b * 4 + 1] * 0x100 +
			guard_data[a * (int)(360 * 4) + b * 4 + 0]);
		line.x++;
	}
	/*
	for (int a = 0; a < 450; a++)
		for (int b = 0; b < 360; b++)
		{
			if (!guard_data[a * (int)(360 * 4) + b * 4 + 3])
				pixel_put(b, a,
				guard_data[a * (int)(360 * 4) + b * 4 + 2] * 0x10000 +
				guard_data[a * (int)(360 * 4) + b * 4 + 1] * 0x100 +
				guard_data[a * (int)(360 * 4) + b * 4 + 0]);
			//guard_data[a * (int)(360 * 4) + b * 4 + 3] * 0x1000000 +
		}
		*/

			//pixel_put(x, y, guard_data[y * line_s + x]);
	//for (int y = line.x; y < line.y; y++)
		//pixel_put(x, y, 0xFF0000);
		//pixel_put_blend(x, y, guard_data[(int)((450 * (y / (line.y - line.x))) * line_s) + (int)(360 * (x / WIN_WIDTH))]);
	//if (settings->cs_mode)
	(void)line;
	(void)x;
}

int		anti_mirror(t_float_xy sprite, t_float_xy cast, t_float_xy location)
{
	sprite.x -= location.x;
	sprite.y -= location.y;
	cast.x -= location.x;
	cast.y -= location.y;

	cast.x -= sprite.x;
	cast.y -= sprite.y;
	double dot = cast.x + cast.y;
	//double dot = sprite.x * cast.x + sprite.y * cast.y;
	//printf("dot = %lf\n", dot);
	//printf("loc.x = %f\n", location.x);
	//printf("loc.y = %f\n", location.y);
	int test = sprite.x + sprite.y;
	if (dot > 0)
		return (1);
	else
		return (0);
	if (dot > 0)
	{
		if (test < sprite.x)
			return (1);
		else
			return (0);
	}
	if (test < sprite.x)
		return (1);
	return (0);
}

int		get_x_offset(t_float_xy sprite, t_float_xy cast, t_float_xy direction, t_float_xy location)
{
	float	center_dist;
	float	prev_dist;

	prev_dist = 10000000;
	//if (fabs(cast.x - sprite.x) - fabs(cast.y - sprite.y) < 0)
	//if (cast.x > sprite.x)
	//float kk  = fabs(fabs(cast.y * 2 - sprite.y) / fabs(cast.x * 2 - sprite.x));
	center_dist = fabs(fabs(cast.x - sprite.x) + fabs(cast.y - sprite.y));

	//if (cast.x > prite.x)
	//if (center_dist < prev_dist)
	//	return (0);
	while (center_dist < prev_dist)
	{
		prev_dist = center_dist;
		cast.x += direction.x;
		cast.y += direction.y;
		center_dist = fabs(fabs(cast.x - sprite.x) + fabs(cast.y - sprite.y));
		//center_dist = fabs(fabs(cast.y * 2 - sprite.y) / fabs(cast.x * 2 - sprite.x));
	}
	center_dist = prev_dist;
	//printf("res = %f\n", center_dist);
	//printf("res = %f\n", 360 * (0 + (center_dist / 0.4)));
	//return ((int)(360 * (center_dist / 0.4)));

	//if (check_neg(sprite, cast, location))
	//	return (0);
	//(void)location;
	if (anti_mirror(sprite, cast, location))
		return ((int)(180 + 360 * (center_dist / 0.8)));
	else
		return ((int)(180 - 360 * (center_dist / 0.8)));
}

void	sprite(t_settings *settings, int x, int stop, t_float_xy direction)
{
	t_float_xy		cast;
	t_float_xy		line;
	int				cast_length;

	static t_float_xy	sprite = {.x = 3.0, .y = 3.0};
	//sprite.x += .01;
	//sprite.y += .01;
	float sprite_dist = 1 * fabs(settings->location.x - sprite.x) + fabs((settings->location.y - sprite.y));
	sprite_dist *= 1000;

	rotate(&direction, FOV * (x + 1));
	int asd;
	while (x++ <= stop)
	{
		cast = settings->location;
		rotate(&direction, FOV);
		cast_length = 1;
		asd = 0;
		while (settings->map[(int)cast.y][(int)cast.x] != '1' && settings->map[(int)cast.y][(int)cast.x] != '2' &&
				settings->map[(int)cast.y][(int)cast.x] != '3' && (cast_length++))
		{
			cast.x += direction.x;
			cast.y += direction.y;
			if (fabs(cast.x - sprite.x) < 0.2 && fabs(cast.y - sprite.y) < 0.2)
			{
				asd = 1;
				break ;
			}
		}
		//printf("cl = %d\n", cast_length);
		//cast_length = sprite_dist;
		//printf("sd = %f\n", sprite_dist);
		(void)sprite_dist;
		//cast_length = 3000;
		//if (settings->map[(int)cast.y][(int)cast.x] == '3')
		if (asd)
		{
			line.x = WIN_HEIGHT / 2 - WMOD / sprite_dist;
			line.y = WIN_HEIGHT / 2 + WMOD / sprite_dist;
			if (line.x < 0)
				line.x = 0;
			if (line.y > WIN_HEIGHT)
				line.y = WIN_HEIGHT;
			//for (int y = line.x; y < line.y; y++)
			//	pixel_put_blend(WIN_WIDTH - 1 - x, y, 0x11FF0000);
			put_sprite(WIN_WIDTH - 1 - x, get_x_offset(sprite, cast, direction, settings->location), line);
		}
	}
	//put_sprite(WIN_WIDTH - 1 - x, line);
}
