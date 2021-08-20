/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/20 17:32:25 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "live_texture.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>

# include <stdio.h>

typedef struct s_xyz {
	float		x;
	float		y;
	float		z;
}				t_xyz;

typedef struct s_fdf_settings {
	unsigned	projection_b : 1;
	unsigned	fov_b : 1;
	float		fov;
	unsigned	spin_b : 1;
	unsigned	color_b : 1;
	t_xyz		color;
	unsigned	cycle_b : 1;
	unsigned	height_b : 1;
	float		height;
	unsigned	height_color_b : 1;
	unsigned	fps_b : 1;
	unsigned	reset_b : 1;
	unsigned	active_layer : 1;
}				t_fdf_settings;

void	text_layer(struct s_fdf_settings *settings);
void	button_layer(struct s_fdf_settings *settings);
void	print_line(t_xyz start, t_xyz stop,
			unsigned int color1, unsigned int color2);
int		get_height(char *filename);
t_xyz	*make_map(int *widht, int *height, char *filename);
int		get_map_len(int n);
int		get_map_width(int n);
double	ft_abs(double n);
void	cycle_colors(t_xyz *color);
void	slider(float *n);
void	ft_error(void);
void	rotate_x(float angle, t_xyz *nodes, int amount);
void	rotate_y(float angle, t_xyz *nodes, int amount);
void	rotate_z(float angle, t_xyz *nodes, int amount);
t_xyz	get_color(int set);
void	draw(t_xyz *nodes, int map_len, struct s_fdf_settings *settings);
t_xyz	add_color_height(t_xyz color);
int		save_coord(int start_i, int stop_i, int which);
void	slider_button(float *n);
void	fdf_set_map(t_xyz *map, int fd, int width, int height);
void	fdf(void);
void	init_fdf(void);
#endif
