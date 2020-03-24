/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/12 20:12:26 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "mlx_io.h"
# include <pthread.h>
# include <math.h>

#include <stdio.h>

typedef struct	s_float_xy {
	float		x;
	float		y;
}				t_float_xy;

typedef struct	s_float_xyz {
	float		x;
	float		y;
	float		z;
}				t_float_xyz;

typedef struct	s_double_xy {
	double		x;
	double		y;
}				t_double_xy;

void	print_line(t_float_xy start, t_float_xy stop, t_float_xy color);

#endif
