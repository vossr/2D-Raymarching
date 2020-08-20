/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/19 21:33:34 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	rotate(t_float_xy *direction, double angle)
{
	double	sin_angle;
	double	cos_angle;
	float	x;
	float	y;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	x = direction->x;
	y = direction->y;
	direction->x = x * cos_angle + y * sin_angle;
	direction->y = y * cos_angle - x * sin_angle;
}

static void	player_movement(t_float_xy *location,
					t_float_xy *direction, t_int_xy map_size, int **map)
{
	if (is_key_down(124))
		rotate(direction, -0.05);
	if (is_key_down(123))
		rotate(direction, 0.05);
	if (is_key_down(126) && 0 == map[(int)(location->x + direction->x * 100)][(int)location->y])
		location->x += direction->x * 100;
	if (is_key_down(126) && 0 == map[(int)location->x][(int)(location->y + direction->y * 100)])
		location->y += direction->y * 100;
	if (is_key_down(125) && 0 == map[(int)(location->x - direction->x * 100)][(int)location->y])
		location->x -= direction->x * 100;
	if (is_key_down(125) && 0 == map[(int)location->x][(int)(location->y - direction->y * 100)])
		location->y -= direction->y * 100;
	if (location->x < 1.1)
		location->x = 1.1;
	else if (location->x > map_size.y - 1.1)
		location->x = map_size.y - 1.1;
	if (location->y < 1.1)
		location->y = 1.1;
	else if (location->y > map_size.x - 1.1)
		location->y = map_size.x - 1.1;
}

#include <stdio.h>
static void	texture_offsets(t_float_xy direction,
				t_float_xy cast, int wall_height, int x, int texture_id)
{
	t_float_xy	line;

	line.x = WIN_HEIGHT / 2 - wall_height;
	line.y = WIN_HEIGHT / 2 + wall_height;
	if ((int)cast.x < (int)(cast.x - direction.x))
	{
		put_texture(x, line, texture_id + 0, 1.0 - (cast.y - (int)cast.y));
	}
	else if ((int)cast.y < (int)(cast.y - direction.y))
	{
		put_texture(x, line, texture_id + 1, cast.x - (int)cast.x);
	}
	else if ((int)cast.y > (int)(cast.y - direction.y))
	{
		put_texture(x, line, texture_id + 2, 1.0 - (cast.x - (int)cast.x));
	}
	else
	{
		put_texture(x, line, texture_id + 3, cast.y - (int)cast.y);
	}
}

static void	put_sprite(int x, int cast_length)
{
	//(void)cast_length;
	for (int y = 0; y < cast_length; y++)
		pixel_put_blend(x, WIN_HEIGHT / 2 - cast_length / 2 + y, 0xDD550000);
}

static void	sprite(t_float_xy location, t_float_xy direction, int **map)
{
	t_float_xy	cast;
	int			x;
	int			cast_length;
	static float fov = 0.00163625;
	static int	wmod = 310000;

	rotate(&direction, -1 * fov * (WIN_WIDTH / 2));
	x = 0;
	while (x < WIN_WIDTH)
	{
		cast = location;
		rotate(&direction, fov);
		cast_length = 1;
		while (map[(int)cast.x][(int)cast.y] == 0)
		{
			cast.x += direction.x;
			cast.y += direction.y;
			cast_length++;
		}
		if (map[(int)cast.x][(int)cast.y] == 3)
			put_sprite(WIN_WIDTH - x - 1, wmod / cast_length / 2);
		x++;
	}
}

static void	raycast(t_float_xy location, t_float_xy direction, int **map)
{
	t_float_xy	cast;
	int			x;
	int			cast_length;
	static float fov = 0.00163625;
	static int	wmod = 310000;

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
	x = 0;
	while (x < WIN_WIDTH)
	{
		cast = location;
		rotate(&direction, fov);
		cast_length = 1;
		while (map[(int)cast.x][(int)cast.y] != 1 && map[(int)cast.x][(int)cast.y] != 2)
		{
			cast.x += direction.x;
			cast.y += direction.y;
			cast_length++;
		}
		//if (map[(int)cast.x][(int)cast.y] != 3)
		texture_offsets(direction, cast, wmod / cast_length,
		WIN_WIDTH - x - 1, (map[(int)cast.x][(int)cast.y] - 1) * 4);
		x++;
	}
}
/*
void	*split_screen(void *settings)
{
	static int	s = 0;

	s++;
	if (s >= THREAD_AMOUNT)
	{
		((t_settings*)settings)->fractal(((t_settings*)settings),
			(HEIGHT / THREAD_AMOUNT) * (s - 1), HEIGHT);
		s = 0;
	}
	else
		((t_settings*)settings)->fractal(((t_settings*)settings),
			(HEIGHT / THREAD_AMOUNT) * (s - 1), (HEIGHT / THREAD_AMOUNT) * s);
	return (NULL);
}

void	print_fractal(t_settings *settings)
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
}*/

int			wolf(void)
{
	static t_float_xy	location = {.x = 1, .y = 1};
	static t_float_xy	direction = {.x = 0.0, .y = .001};
	static t_int_xy		map_size;
	static int			**map = NULL;

	if (is_key_down(53))
		exit(0);
	else if (!map)
		map = read_map(NULL, &map_size);
	player_movement(&location, &direction, map_size, map);
	raycast(location, direction, map);
	sprite(location, direction, map);
	map_print(location, map_size, map);
	update_image();
	fps();
	return (0);
}
