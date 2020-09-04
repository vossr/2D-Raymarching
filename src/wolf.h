/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/09/03 20:58:55 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "mlx_io.h"
# include <CoreGraphics/CoreGraphics.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <math.h>
# define THREAD_AMOUNT 1
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
	t_float_xy	cast_dir;
	t_int_xy	map_size;
	char		**map;
	int			menu;
	int			fps;
	int			print_map;
	int			cs_mode;
}				t_settings;

typedef struct	s_button {
	int			x;
	int			y;
	int			size_x;
	int			is_on;
	char		*text;
}				t_button;

void			buttons(t_settings *settings);
t_button		*init_buttons(void);
int				handle_button(t_button b);
void			read_map(char **argv, t_settings *settings, int next);
void			map_print(t_settings *settings);
void			put_texture(int line_x, t_float_xy line,
								int texture_id, float texture_x);
void			fps(void);
void			fatal_error(char *error);
void			set_start(t_settings *settings);
void			make_threads(t_settings *settings);
void			rotate(t_float_xy *direction, double angle);
void			crosshair(void);
void			put_gun(t_settings *settings);
void			capture_cursor(t_settings *settings);
void			sprite(t_settings *settings, int x, int stop, t_float_xy direction);
#endif
