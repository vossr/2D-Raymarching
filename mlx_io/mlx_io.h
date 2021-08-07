/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_io.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 11:37:00 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_IO_H
# define MLX_IO_H
# include "mlx.h"
# include "libft.h"

typedef struct s_int_xy {
	int			x;
	int			y;
}				t_int_xy;

int				handle_keyboard_down(int key);
int				handle_keyboard_up(int key);
int				loop_hook(void);
void			**get_mlx(void **mlx);
t_int_xy		get_window_size(void);
int				wolf(void);
void			init_window(int width, int height, char *filename);
int				is_key_down(int key);
void			update_image(void);
void			pixel_put(int x, int y, unsigned int color);
#endif
