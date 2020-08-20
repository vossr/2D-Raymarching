/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/20 15:29:32 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <stdio.h>
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
	t_int_xy loc_on_map_f;
	t_int_xy loc_on_map_b;
	int speed;

	if ((is_key_down(126) || is_key_down(125)) && (is_key_down(124) || is_key_down(123)))
		speed = 80;
	else
		speed = 60;
	if (is_key_down(124))
		rotate(direction, -0.05);
	if (is_key_down(123))
		rotate(direction, 0.05);
	loc_on_map_f.x = map[(int)(location->x + direction->x * speed)][(int)location->y];
	loc_on_map_f.y = map[(int)location->x][(int)(location->y + direction->y * speed)];
	loc_on_map_b.x = map[(int)(location->x - direction->x * speed)][(int)location->y];
	loc_on_map_b.y = map[(int)location->x][(int)(location->y - direction->y * speed)];
	if (is_key_down(126) && 1 != loc_on_map_f.x && 2 != loc_on_map_f.x && loc_on_map_f.x != 3)
		location->x += direction->x * speed;
	if (is_key_down(126) && 1 != loc_on_map_f.y && 2 != loc_on_map_f.y && loc_on_map_f.y != 3)
		location->y += direction->y * speed;
	if (is_key_down(125) && 1 != loc_on_map_b.x && 2 != loc_on_map_b.x && loc_on_map_b.x != 3)
		location->x -= direction->x * speed;
	if (is_key_down(125) && 1 != loc_on_map_b.y && 2 != loc_on_map_b.y && loc_on_map_b.y != 3)
		location->y -= direction->y * speed;
	(void)map_size;
	if (map[(int)location->x][(int)(location->y)] == 4)
	{
		//load next map
		printf("Victory\n");
		exit(0);
	}
}

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

void	**load_gun(int *line_s)
{
	void	**mlx = NULL;
	void	**texture;
	int			bps;

	texture = (void**)malloc(sizeof(void*) * 2);
	mlx = get_mlx(NULL);
	texture[0] = mlx_xpm_file_to_image(mlx[0], "textures/flash.xpm", &bps, line_s);
	texture[1] = mlx_xpm_file_to_image(mlx[0], "textures/gun.xpm", &bps, line_s);
	if (texture[0] == NULL || texture[1] == NULL)
	{
		printf("gun load fail\n");
		exit(0);
	}
	return (texture);
}

void	put_gun(void)
{
	static void **gun = NULL;
	static int line_s;
	static void	**mlx = NULL;

	if (!gun)
	{
		gun = load_gun(&line_s);
		mlx = get_mlx(NULL);
	}
	static int last = 0;

	if (last && is_mouse_down(1))
		mlx_put_image_to_window(mlx[0], mlx[1], gun[0], WIN_WIDTH / 2 + 20, WIN_HEIGHT - 200 - 20);
	last = 1;
	if (is_mouse_down(1))
		last = 0;
	mlx_put_image_to_window(mlx[0], mlx[1], gun[1], WIN_WIDTH / 2, WIN_HEIGHT - 200);
}

int			wolf(void)
{
	static t_settings settings;

	if (is_key_down(53))
		exit(0);
	else if (!settings.map)
	{
		settings.location.x = 1.5;
		settings.location.y = 1.5;
		settings.direction.x = 0.0;
		settings.direction.y = 0.001;
		settings.map = read_map(NULL, &settings.map_size);
	}
	player_movement(&settings.location, &settings.direction, settings.map_size, settings.map);
	raycast(settings.location, settings.direction, settings.map);
	sprite(settings.location, settings.direction, settings.map);
	map_print(settings.location, settings.map_size, settings.map);
	update_image();
	put_gun();
	fps();
	return (0);
}
