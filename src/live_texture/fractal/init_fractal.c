/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/19 21:09:30 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

t_f_settings	*init_settings(int fractal)
{
	static t_f_settings	settings;

	if (!fractal)
		return (&settings);
	settings.max_iter = 50;
	settings.max_i_modifier = 50;
	settings.pos.x = 0;
	settings.pos.y = 0;
	settings.zoom = 3;
	return (NULL);
}

void	init_fractal(void)
{
	init_settings(42);
}
