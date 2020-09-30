/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/11 17:09:12 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

t_f_settings	*init_settings(int fractal)
{
	static t_f_settings	settings;

	if (!fractal)
		return (&settings);
///	if (fractal == 1)
///		settings.fractal = &mandelbrot;
///	else
///		settings.fractal = fractal == 2 ? &julia : &burningship;
	settings.fractal = &julia;
	settings.fractal_id = fractal;
	settings.max_iter = 50;
	settings.max_i_modifier = 50;
	if (fractal != 3)
	{
		settings.pos.x = 0;
		settings.pos.y = 0;
		settings.zoom = 3;
		settings.color = 6;
		return (NULL);
	}
	settings.pos.x = -175;
	settings.pos.y = -3;
	settings.zoom = 3;
	settings.color = 6;
	return (NULL);
}

void		put_usage(char *arg)
{
	ft_putstr("usage: ");
	ft_putstr(arg);
	ft_putstr(" [mandelbrot | julia | burningship]\n");
}

void		init_fractal(void)
{
	init_settings(2);
}
