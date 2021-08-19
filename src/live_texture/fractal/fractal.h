/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/19 21:10:55 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "live_texture.h"
# include <pthread.h>
# include <math.h>
# define F_THREAD_AMOUNT 4
# define PRECISION double

typedef struct s_position_xy {
	PRECISION		x;
	PRECISION		y;
}					t_position_xy;

typedef struct s_f_settings {
	t_position_xy	pos;
	PRECISION		zoom;
	int				max_iter;
	int				max_i_modifier;
	int				frame;
}					t_f_settings;

typedef struct s_thread_data {
	t_f_settings	*settings;
	int				id;
}					t_thread_data;

void			init_fractal(void);
void			fractal(void);
void			julia(t_f_settings *settings, int start, int stop);
t_f_settings	*init_settings(int i);
#endif
