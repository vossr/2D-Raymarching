/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/15 13:18:22 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "mlx_io.h"
# include <pthread.h>
# include <math.h>
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

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

void	print_line(t_float_xy start, t_float_xy stop, int color);
void	map_print(t_float_xy location, t_float_xy direction, t_int_xy map_size, int **map);
int		**read_map(char *str, t_int_xy *map_size);
#endif
