/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/11 16:47:53 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "live_texture.h"
# include <pthread.h>
# include <math.h>
# define F_THREAD_AMOUNT 6
# define PRECISION double
# define WIDTH 512
# define HEIGHT 512
# define ASPECT_WIDTH 1.0
# define ASPECT_HEIGHT 1.0

typedef struct		s_position_xy {
	PRECISION		x;
	PRECISION		y;
}					t_position_xy;

typedef struct		s_f_settings {
	t_position_xy	pos;
	PRECISION		zoom;
	int				max_iter;
	int				max_i_modifier;
	int				color;
	int				frame;
	int				fractal_id;
	void			(*fractal)(struct s_f_settings*, int, int);
}					t_f_settings;

//void				mandelbrot(t_settings *settings, int start, int stop);
void				julia(t_f_settings *settings, int start, int stop);
//void				burningship(t_settings *settings, int start, int stop);
t_f_settings			*init_settings(int i);
void				color_settings(t_f_settings *settings);
int					select_color(int color, int max, int frame, int iteration);
#endif
