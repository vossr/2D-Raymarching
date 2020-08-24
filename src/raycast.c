/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 19:47:35 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/24 19:49:26 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	texture_offsets(t_float_xy direction, t_float_xy cast,
									int *wall_dir, float *texture_x)
{
	if ((int)cast.x != (int)(cast.x - direction.x) &&
				(int)cast.y != (int)(cast.y - direction.y))
		return ;
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

static void	raycast(t_settings *settings, int start, int stop)
{
	static float	fov = 0.00163625;
	static int		wmod = 310000;
	t_float_xy		direction;
	t_float_xy		cast;
	t_float_xy		line;
	int				cast_length;
	int				wall_height;
	int				texture_id;
	int				x;
	int				wall_dir;
	float			tex_x;

	wall_dir = 0;
	direction = settings->direction;
	if (is_key_down(18))
		wmod += 10000;
	if (is_key_down(19))
		wmod -= 10000;
	if (is_key_down(20))
		fov += 0.0001;
	if (is_key_down(21))
		fov -= 0.0001;
	//printf("fov = %f\n", fov);
	//printf("wmod = %d\n", wmod);
	rotate(&direction, -1 * fov * (WIN_WIDTH / 2));
	rotate(&direction, fov * (start));
	x = start;
	while (x < stop)
	{
		cast = settings->location;
		rotate(&direction, fov);
		cast_length = 1;
		while (settings->map[(int)cast.y][(int)cast.x] != '1' &&
					settings->map[(int)cast.y][(int)cast.x] != '2')
		{
			cast.x += direction.x;
			cast.y += direction.y;
			cast_length++;
		}
		texture_id = (settings->map[(int)cast.y][(int)cast.x] - 1 - '0') * 4;
		if (settings->cs_mode)
			texture_id = 8;
		wall_height = wmod / cast_length;
		line.x = WIN_HEIGHT / 2 - wall_height;
		line.y = WIN_HEIGHT / 2 + wall_height;
		texture_offsets(direction, cast, &wall_dir, &tex_x);
		put_texture(WIN_WIDTH - 1 - x, line, texture_id + wall_dir, tex_x);
		x++;
	}
}

void	test(t_settings *settings, int id)
{
	int scale;

	scale = WIN_WIDTH / THREAD_AMOUNT;
	raycast(settings, scale * (id - 1), scale * id);
}

void	*split_screen(void *settings)
{
	static int	s = 0;

	s++;
	test(((t_settings*)settings), s);
	if (s >= THREAD_AMOUNT)
		s = 0;
	return (NULL);
}

void	make_threads(t_settings *settings)
{
	pthread_t	tid[THREAD_AMOUNT];
	int			i;

	i = 0;
	while (i < THREAD_AMOUNT)
	{
		pthread_create(&tid[i], NULL, split_screen, (void*)settings);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < THREAD_AMOUNT)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
}
