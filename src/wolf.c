/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/20 19:00:03 by rpehkone         ###   ########.fr       */
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

void		collision(t_float_xy *location, t_float_xy *direction, int neg, int **map)
{
	int speed = 40;
	t_int_xy	loc_on_map_f;

	loc_on_map_f.y = map[(int)(location->y + neg * direction->y * speed)][(int)location->x];
	loc_on_map_f.x = map[(int)location->y][(int)(location->x + neg * direction->x * speed)];
	if (1 != loc_on_map_f.x && 2 != loc_on_map_f.x && loc_on_map_f.x != 3)
		location->x += direction->x * speed * neg;
	if (1 != loc_on_map_f.y && 2 != loc_on_map_f.y && loc_on_map_f.y != 3)
		location->y += direction->y * speed * neg;
}

static void	player_movement(t_settings *settings)
{
	t_int_xy	cursor;
	t_float_xy	tangent;
	int fwd;
	int bwd;

	fwd = is_key_down(126) + is_key_down(13);
	bwd = is_key_down(125) + is_key_down(1);
	cursor = get_cursor();
	int32_t deltaY;
	int32_t deltaX;
	CGGetLastMouseDelta(&deltaX, &deltaY);
	if (deltaX)
		rotate(&settings->direction, deltaX * -0.005);
	if (is_key_down(124))
		rotate(&settings->direction, -0.05);
	if (is_key_down(123))
		rotate(&settings->direction, 0.05);
	if (fwd)
		collision(&settings->location, &settings->direction, 1, settings->map);
	if (bwd)
		collision(&settings->location, &settings->direction, -1, settings->map);
	tangent = settings->direction;
	rotate(&tangent, 1.57079633);
	if (is_key_down(0))
		collision(&settings->location, &tangent, 1, settings->map);
	if (is_key_down(2))
		collision(&settings->location, &tangent, -1, settings->map);
	if (settings->map[(int)settings->location.x][(int)(settings->location.y)] == 4)
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

/*
static void	put_sprite(int x, int cast_length)
{
	//(void)cast_length;
	for (int y = 0; y < cast_length; y++)
		pixel_put_blend(x, WIN_HEIGHT / 2 - cast_length / 2 + y, 0xDD550000);
}

static void	sprite(t_float_xy location, t_float_xy direction, int **map, int start, int stop)
{
	t_float_xy	cast;
	int			x;
	int			cast_length;
	static float fov = 0.00163625;
	static int	wmod = 310000;

	rotate(&direction, -1 * fov * (WIN_WIDTH / 2));
	rotate(&direction, fov * (start));
	x = start;
	while (x < stop)
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
			put_sprite(WIN_WIDTH - x - 1, wmod / cast_length);
		x++;
	}
}
*/

static void	raycast(t_float_xy location, t_float_xy direction, int **map, int start, int stop)
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
	rotate(&direction, fov * (start));
	x = start;
	while (x < stop)
	{
		cast = location;
		rotate(&direction, fov);
		cast_length = 1;
		while (map[(int)cast.y][(int)cast.x] != 1 && map[(int)cast.y][(int)cast.x] != 2)
		{
			cast.x += direction.x;
			cast.y += direction.y;
			cast_length++;
		}
		//if (map[(int)cast.x][(int)cast.y] != 3)
		texture_offsets(direction, cast, wmod / cast_length,
		WIN_WIDTH - x - 1, (map[(int)cast.y][(int)cast.x] - 1) * 4);
		x++;
	}
}

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

void	crosshair(void)
{
	int x = WIN_WIDTH / 2;
	int y = WIN_HEIGHT / 2;
	int i;
	int j;

	i = -1;
	while (++i < 10 && (j = -1))
		while (++j < 3)
		{
			pixel_put(x + i - 14, y + j, 0xFF00);
			pixel_put(x + i + 4, y + j, 0xFF00);
		}
	i = -1;
	while (++i < 3 && (j = -1))
		while (++j < 10)
		{
			pixel_put(x + i - 1, y + j - 14, 0xFF00);
			pixel_put(x + i - 1, y + j + 6, 0xFF00);
		}
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
	mlx_put_image_to_window(mlx[0], mlx[1], gun[1], WIN_WIDTH / 2, WIN_HEIGHT - 200);
	last = 1;
	if (is_mouse_down(1))
		last = 0;
}

void	test(t_settings *settings, int id)
{
	int scale = WIN_WIDTH / THREAD_AMOUNT;
	raycast(settings->location, settings->direction, settings->map, scale * (id - 1), scale * id);
	//sprite(settings->location, settings->direction, settings->map, scale * (id - 1), scale * id);
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

void		capture_cursor(void)
{
	UInt32 dispid;
	dispid = CGMainDisplayID();
	CGDisplayHideCursor(dispid);
	CGPoint cursor;
	cursor.x = 700;
	cursor.y = 700;
	//move releative to window;
	CGWarpMouseCursorPosition(cursor);
}

int			wolf(void)
{
	static t_settings settings;

	if (is_key_down(53))
		exit(0);
	else if (!settings.map)
		read_map(NULL, &settings);
	player_movement(&settings);
	make_threads(&settings);
	map_print(&settings);
	crosshair();
	update_image();
	put_gun();
	//buttons(&settings);
	fps();
	capture_cursor();
	return (0);
}
