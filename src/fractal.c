/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/12 18:32:06 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		mandelbrot(float cx, float cy, int max_iter)
{
	float	zx;
	float	zy;
	float	tempx;
	int		iteration;

	zx = 0;
	zy = 0;
	iteration = 0;
	while ((zx * zx + zy * zy < 4) && (iteration < max_iter))
	{
		tempx = zx * zx - zy * zy + cx;
		zy = 2 * zx * zy + cy;
		zx = tempx;
		iteration++;
	}
	return (iteration);
}

int		julia(float cx, float cy, int max_iter, t_float_xy pos)
{
	float	zx;
	float	zy;
	float	tempx;
	int		iteration;

	zx = 0;
	zy = 0;
	iteration = 0;
	zx = cx;
	zy = cy;
	cx = (3.0 / 1280) * (pos.x - 1280 / 2);
	cy = (2.0 / 720) * (pos.y - 720 / 2);
	while ((zx * zx + zy * zy < 4) && (iteration < max_iter))
	{
		tempx = zx * zx - zy * zy + cx;
		zy = 2 * zx * zy + cy;
		zx = tempx;
		iteration++;
	}
	return (iteration);
}

void	mandelbrot_loop(t_float_xy pos, float zoom, int max_iter, int i)
{
	float	cx;
	float	cy;
	int		x;
	int		y;

	y = 0;
	if (i == 720)
		y = 540;
	else if (i == 540)
		y = 360;
	else if (i == 360)
		y = 180;
	while (y < i)
	{
		x = 0;
		while (x < 1280)
		{
			cx = (x - 640) * ((16.0 * zoom) / 1280) + pos.x;
			cy = (y - 360) * ((9.0 * zoom) / 720) + pos.y;
			pixel_put(x, y, 0xFF - mandelbrot(cx, cy, max_iter) * 10);
			x++;
		}
		y++;
	}
}

void	julia_loop(t_float_xy pos, float zoom, int max_iter, int i)
{
	float	cx;
	float	cy;
	int		x;
	int		y;

	y = 0;
	if (i == 720)
		y = 540;
	else if (i == 540)
		y = 360;
	else if (i == 360)
		y = 180;
	while (y < i)
	{
		x = 0;
		while (x < 1280)
		{
			cx = (x - 640) * ((16.0 * zoom) / 1280);
			cy = (y - 360) * ((9.0 * zoom) / 720);
			pixel_put(x, y, 0xFF - julia(cx, cy, max_iter, pos) * 10);
			x++;
		}
		y++;
	}
}

int		set_fractal(int f)
{
	static int	fractal_id = -1;

	if (!f)
		return (fractal_id);
	if (fractal_id == -1)
		fractal_id = f;
	return (0);
}

void	what_fractal(t_float_xy pos, float zoom, int max_iter, int i)
{
	if (set_fractal(0) == 1)
	{
		pos.x /= (100 / zoom);
		pos.y /= (100 / zoom);
		mandelbrot_loop(pos, zoom, max_iter, i);
	}
	else if (set_fractal(0) == 2)
	{
		pos.x *= 10;
		pos.y *= 10;
		julia_loop(pos, zoom, max_iter, i);
	}
	else if (set_fractal(0) == 3)
		;//burningship_loop(pos, zoom, max_iter, i);
}

void	*split_threads(void *args)
{
	static int	s = 0;

	s++;
	if (s == 1)
		what_fractal(((t_mand*)args)->pos, ((t_mand*)args)->zoom,
				((t_mand*)args)->max_iter, 720);
	else if (s == 2)
		what_fractal(((t_mand*)args)->pos, ((t_mand*)args)->zoom,
				((t_mand*)args)->max_iter, 540);
	else if (s == 3)
		what_fractal(((t_mand*)args)->pos, ((t_mand*)args)->zoom,
				((t_mand*)args)->max_iter, 360);
	else if (s == 4)
	{
		what_fractal(((t_mand*)args)->pos, ((t_mand*)args)->zoom,
				((t_mand*)args)->max_iter, 180);
		s = 0;
	}
	return (NULL);
}

void	make_threads(t_float_xy pos, float zoom, int max_iter)
{
	static t_mand	args;
	pthread_t		tid[4];
	int				i;

	args.pos = pos;
	args.zoom = zoom;
	args.max_iter = max_iter;
	i = 0;
	while (i < 4)
	{
		pthread_create(&tid[i], NULL, split_threads, (void*)&args);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
}

void	engine(void)
{
	static t_float_xy	pos = {.x = 0, .y = 0};
	static t_int_xy		oldc;
	static float		zoom = .3;
	static int			max_iter = 20;
	t_int_xy			c;

	c = get_cursor();
	if (is_key_down(53))
		exit(0);
	if (set_fractal(0) == 2 || is_mouse_down(1))
	{
		pos.x -= ((float)c.x - oldc.x);
		pos.y -= ((float)c.y - oldc.y);
	}
	if (is_mouse_down(4))
		zoom *= 1.3;
	if (is_mouse_down(5))
		zoom *= (1.0 / 1.3);
	max_iter = is_key_down(126) ? max_iter + 1 : max_iter;
	max_iter = is_key_down(125) ? max_iter - 1 : max_iter;
	max_iter = max_iter < 0 ? 0 : max_iter;
	oldc.x = c.x;
	oldc.y = c.y;
	make_threads(pos, zoom, max_iter);
}
