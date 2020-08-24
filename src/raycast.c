/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 19:47:35 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/24 21:32:27 by rpehkone         ###   ########.fr       */
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

static void	raycast(t_settings *settings, int x, int stop, t_float_xy direction)
{
	t_float_xy		cast;
	t_float_xy		line;
	int				cast_length;
	int				wall_dir;
	float			tex_x;

	wall_dir = 0;
	rotate(&direction, FOV * (x + 1));
	while (x++ <= stop)
	{
		cast = settings->location;
		rotate(&direction, FOV);
		cast_length = 1;
		while (settings->map[(int)cast.y][(int)cast.x] != '1' && settings->
			map[(int)cast.y][(int)cast.x] != '2' && (cast_length++))
		{
			cast.x += direction.x;
			cast.y += direction.y;
		}
		line.x = WIN_HEIGHT / 2 - WMOD / cast_length;
		line.y = WIN_HEIGHT / 2 + WMOD / cast_length;
		texture_offsets(direction, cast, &wall_dir, &tex_x);
		put_texture(WIN_WIDTH - 1 - x, line, settings->cs_mode ? 8 : (settings->
			map[(int)cast.y][(int)cast.x] - 1 - '0') * 4 + wall_dir, tex_x);
	}
}

void		*split_screen(void *settings)
{
	static int	id = 0;
	int			scale;

	id++;
	scale = WIN_WIDTH / THREAD_AMOUNT;
	raycast((t_settings*)settings, scale * (id - 1) + 1, scale * id,
							((t_settings*)settings)->cast_dir);
	if (id >= THREAD_AMOUNT)
		id = 0;
	return (NULL);
}

void		make_threads(t_settings *settings)
{
	pthread_t	tid[THREAD_AMOUNT];
	int			i;

	i = 0;
	settings->cast_dir = settings->direction;
	rotate(&settings->cast_dir, -1 * FOV * (WIN_WIDTH / 2));
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
