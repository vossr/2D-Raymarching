/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/19 02:43:01 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

t_f_settings	*init_settings(int fractal)
{
	static t_f_settings	settings;

	if (!fractal)
		return (&settings);
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

void	init_fractal(void)
{
	init_settings(2);
}
