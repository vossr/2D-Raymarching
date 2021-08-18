/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/18 23:11:41 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "mlx_io.h"
# include "live_texture.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# define WIN_WIDTH 800
# define WIN_HEIGHT 500
# define FOV 50.0
# define PLAYER_SPEED 0.05
# define STEP_LEN 0.001

typedef struct s_vec2 {
	double		x;
	double		y;
}				t_vec2;

typedef struct s_settings {
	t_vec2		location;
	double		angle;
	double		ray_angle;
	int			map_width;
	int			map_height;
	char		**map;
}				t_settings;

void			fatal_error(char *error);
double			deg_to_rad(double d);
t_settings		*init(char *filename);
void			raycast(t_settings *settings);
#endif
