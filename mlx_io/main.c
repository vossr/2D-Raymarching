/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/12 17:01:10 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(char *error)
{
	ft_putstr(error);
	ft_putchar('\n');
	exit(0);
}

void	init_window(char *title)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	**mlx;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1280, 720, title);
	img_ptr = mlx_new_image(mlx_ptr, 1280, 720);
	if (!(mlx = (void **)malloc(sizeof(void *) * 3)))
		ft_error("malloc fail");
	mlx[0] = mlx_ptr;
	mlx[1] = win_ptr;
	mlx[2] = img_ptr;
	get_mlx(mlx);
	mlx_hook(win_ptr, 2, 0, handle_keyboard_down, mlx);
	mlx_hook(win_ptr, 3, 0, handle_keyboard_up, mlx);
	mlx_hook(win_ptr, 4, 0, handle_mouse_down, mlx);
	mlx_hook(win_ptr, 5, 0, handle_mouse_up, mlx);
	mlx_hook(win_ptr, 6, 0, handle_cursor, mlx);
	mlx_loop_hook(mlx_ptr, loop_hook, mlx);
	mlx_loop(mlx_ptr);
}

void	put_usage(char *arg)
{
		ft_putstr("usage: ");
		ft_putstr(arg);
		ft_putstr(" [mandelbrot | julia | burningship]\n");
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		put_usage(argv[0]);
	else if (!ft_strcmp(argv[1], "mandelbrot"))
	{
		set_fractal(1);
		init_window("mandlelbrot");
	}
	else if (!ft_strcmp(argv[1], "julia"))
	{
		set_fractal(2);
		init_window("julia");
	}
	else if (!ft_strcmp(argv[1], "burningship"))
	{
		set_fractal(3);
		init_window("burningship");
	}
	else
		put_usage(argv[0]);
	return (0);
}
