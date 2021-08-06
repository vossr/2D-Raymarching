/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/06 13:18:43 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "mlx_io.h"
# include <sys/time.h>
# include <fcntl.h>
# include <math.h>
#include <stdio.h>//del
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define FOV 61.0
# define WMOD 310000
#define RAY_PREC 800

typedef struct	s_float_xy {
	float		x;
	float		y;
}				t_float_xy;

typedef struct	s_settings {
	t_float_xy	location;
	float		angle;
	int			map_width;
	int			map_height;
	char		**map;
}				t_settings;

t_settings		*read_map(char *filename);

void			put_texture(int line_x, t_float_xy line,
								int texture_id, float texture_x);
void			fatal_error(char *error);
float			deg_to_rad(float d);
void			raycast(t_settings *settings);
#endif
