/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/05 19:30:12 by rpehkone         ###   ########.fr       */
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
# define FOV 0.00163625
# define WMOD 310000

typedef struct	s_float_xy {
	float		x;
	float		y;
}				t_float_xy;

typedef struct	s_settings {
	t_float_xy	location;
	t_float_xy	direction;
	int			map_width;
	int			map_height;
	char		**map;
}				t_settings;

t_settings		*read_map(char *filename);

void			put_texture(int line_x, t_float_xy line,
								int texture_id, float texture_x);
void			fatal_error(char *error);
void			rotate(t_float_xy *direction, double angle);
void			raycast(t_settings *settings);
#endif
