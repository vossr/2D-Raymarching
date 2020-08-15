/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 20:58:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/15 13:12:50 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_io.h"

void		**get_mlx(void **mlx)
{
	static void	**mlx_save = NULL;

	if (!mlx)
		return (mlx_save);
	mlx_save = mlx;
	return (mlx_save);
}

t_int_xy	set_window_size(int w, int h)
{
	static t_int_xy window_size = {.x = 0, .y = 0};

	if (w)
	{
		window_size.x = w;
		window_size.y = h;
	}
	return (window_size);
}

t_int_xy	get_window_size(void)
{
	return (set_window_size(0, 0));
}

int			handle_exit(void)
{
	exit(0);
}

void		init_window(int w, int h, char *title)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	**mlx;

	mlx_ptr = mlx_init();
	set_window_size(w, h);
	win_ptr = mlx_new_window(mlx_ptr, w, h, title);
	img_ptr = mlx_new_image(mlx_ptr, w, h);
	if (!(mlx = (void **)malloc(sizeof(void *) * 3)))
		exit(0);
	mlx[0] = mlx_ptr;
	mlx[1] = win_ptr;
	mlx[2] = img_ptr;
	get_mlx(mlx);
	mlx_hook(win_ptr, 2, 0, handle_keyboard_down, mlx);
	mlx_hook(win_ptr, 3, 0, handle_keyboard_up, mlx);
	mlx_hook(win_ptr, 4, 0, handle_mouse_down, mlx);
	mlx_hook(win_ptr, 5, 0, handle_mouse_up, mlx);
	mlx_hook(win_ptr, 6, 0, handle_cursor, mlx);
	mlx_hook(win_ptr, 17, 0, handle_exit, mlx);
	mlx_loop_hook(mlx_ptr, wolf, mlx);
	mlx_loop(mlx_ptr);
}
