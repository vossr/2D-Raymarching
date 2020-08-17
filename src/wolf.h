/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/17 13:34:05 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "mlx_io.h"
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <math.h>
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

typedef struct	s_float_xy {
	float		x;
	float		y;
}				t_float_xy;

typedef struct	s_float_xyz {
	float		x;
	float		y;
	float		z;
}				t_float_xyz;
/////////poista
typedef struct	s_double_xy {
	double		x;
	double		y;
}				t_double_xy;

int				**read_map(char *str, t_int_xy *map_size);
void			map_print(t_float_xy location, t_int_xy map_size, int **map);
void			put_texture(int line_x, t_float_xy line,
								int texture_id, float texture_x);
void			fps(void);
#endif
