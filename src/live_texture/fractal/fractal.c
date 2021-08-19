/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/19 21:14:30 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	*frac_split_screen(void *get_data)
{
	t_thread_data	*data;

	data = (t_thread_data *)get_data;
	julia(data->settings,
		(LIVE_TEXTURE_SIZE / F_THREAD_AMOUNT) * data->id,
		(LIVE_TEXTURE_SIZE / F_THREAD_AMOUNT) * (data->id + 1));
	return (NULL);
}

void	print_fractal(t_f_settings *settings)
{
	t_thread_data	data[F_THREAD_AMOUNT];
	pthread_t		tid[F_THREAD_AMOUNT];
	int				i;

	i = 0;
	while (i < F_THREAD_AMOUNT)
	{
		data[i].settings = settings;
		data[i].id = i;
		pthread_create(&tid[i], NULL, frac_split_screen, (void *)&data[i]);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < F_THREAD_AMOUNT)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
}

void	frac_rotate(t_position_xy *direction, double angle)
{
	double		sin_angle;
	double		cos_angle;
	PRECISION	x;
	PRECISION	y;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	x = direction->x;
	y = direction->y;
	direction->x = x * cos_angle + y * sin_angle;
	direction->y = y * cos_angle - x * sin_angle;
}

t_int_xy	spinner(void)
{
	static t_position_xy	fake_cursor = {.x = LIVE_TEXTURE_SIZE / 4,
		.y = LIVE_TEXTURE_SIZE / 4};
	t_int_xy				res;

	frac_rotate(&fake_cursor, -0.02);
	res.x = LIVE_TEXTURE_SIZE / 2 + (int)fake_cursor.x;
	res.y = LIVE_TEXTURE_SIZE / 2 + (int)fake_cursor.y;
	return (res);
}

void	fractal(void)
{
	static t_f_settings	*settings = NULL;
	static t_int_xy		oldc;
	t_int_xy			cursor;

	if (is_key_down(53))
		exit(0);
	if (!settings)
		settings = init_settings(0);
	cursor = spinner();
	settings->pos.x -= ((PRECISION)cursor.x - oldc.x);
	settings->pos.y -= ((PRECISION)cursor.y - oldc.y);
	if (settings->max_iter < 0)
		settings->max_iter = 0;
	else if (settings->max_iter > 120)
		settings->max_iter = 120;
	oldc.x = cursor.x;
	oldc.y = cursor.y;
	settings->frame = settings->frame == 0;
	print_fractal(settings);
}
