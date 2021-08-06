/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/06 14:29:42 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "mlx_io.h"
# include <sys/time.h>
# include <fcntl.h>
# include <math.h>
#include <stdio.h>//del
# define WIN_WIDTH 900
# define WIN_HEIGHT 720
# define FOV 61.0
# define RAY_PREC 800

typedef struct	s_float_xy {
	float		x;
	float		y;
}				t_float_xy;

typedef struct	s_settings {
	t_float_xy	location;
	float		angle;
	float		ray_angle;
	int			map_width;
	int			map_height;
	char		**map;
}				t_settings;

void			fatal_error(char *error);
float			deg_to_rad(float d);
t_settings		*read_map(char *filename);
void			raycast(t_settings *settings);
#endif
