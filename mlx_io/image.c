/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:04:17 by rpehkone          #+#    #+#             */
/*   Updated: 2020/07/30 12:20:43 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_io.h"

void	clear_image(void)
{
	static char	*data = NULL;
	static int	pixels;
	void		**mlx;
	t_int_xy	win_size;

	if (!data)
	{
		mlx = get_mlx(NULL);
		data = mlx_get_data_addr(mlx[2], &pixels, &win_size.x, &win_size.y);
		win_size = get_window_size();
		pixels = win_size.x * win_size.y * 4;
	}
	ft_memset(data, 0, pixels);
}

void	update_image(void)
{
	static void **mlx = NULL;

	if (!mlx)
		mlx = get_mlx(NULL);
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
	clear_image();
}

void	pixel_put_blend(int x, int y, unsigned color)
{
	static unsigned char		*data = NULL;
	static t_int_xy	win_size;
	void			**mlx;
	int				dummy;

	if (!data)
	{
		mlx = get_mlx(NULL);
		data = (unsigned char*)mlx_get_data_addr(mlx[2], &win_size.y, &win_size.x, &dummy);
		dummy = win_size.x;
		win_size = get_window_size();
		win_size.x = dummy;
	}
	if (x * 4 >= win_size.x || y >= win_size.y || x < 0 || y < 0)
		return ;
	//data[(y * win_size.x) + (x * 4) + 3] = (char)(color>>8 * 3);

	unsigned char red = ((color << 8 * 1) >> 8 * 3) * (color >> 8 * 3);
	if (red + data[(y * win_size.x) + (x * 4) + 2] > 255)
		red = 255;
	else if (red + data[(y * win_size.x) + (x * 4) + 2] < 0)
		red = 0;
	else
		red = red + data[(y * win_size.x) + (x * 4) + 2];
	data[(y * win_size.x) + (x * 4) + 2] = red;

	unsigned char grn = ((color << 8 * 2) >> 8 * 3) * (color >> 8 * 3);
	if (grn + data[(y * win_size.x) + (x * 4) + 1] > 255)
		grn = 255;
	else if (red + data[(y * win_size.x) + (x * 4) + 1] < 0)
		grn = 0;
	else
		grn = grn + data[(y * win_size.x) + (x * 4) + 1];
	data[(y * win_size.x) + (x * 4) + 1] = grn;


	unsigned char blu = ((color << 8 * 3) >> 8 * 3) * (color >> 8 * 3);
	if (blu + data[(y * win_size.x) + (x * 4) + 0] > 255)
		blu = 255;
	else if (blu + data[(y * win_size.x) + (x * 4) + 0] < 0)
		blu = 0;
	else
		blu = blu + data[(y * win_size.x) + (x * 4) + 0];
	data[(y * win_size.x) + (x * 4) + 0] = blu;

/*
	data[(y * win_size.x) + (x * 4) + 2] = (color % 0x1000000) >> 4 * 4;
	data[(y * win_size.x) + (x * 4) + 1] = (color % 0x1000000) >> 4 * 2;
	data[(y * win_size.x) + (x * 4) + 0] = color % 0x1000000;
*/
}

void	pixel_put(int x, int y, unsigned color)
{
	static unsigned char		*data = NULL;
	static t_int_xy	win_size;
	void			**mlx;
	int				dummy;

	if (!data)
	{
		mlx = get_mlx(NULL);
		data = (unsigned char*)mlx_get_data_addr(mlx[2], &win_size.y, &win_size.x, &dummy);
		dummy = win_size.x;
		win_size = get_window_size();
		win_size.x = dummy;
	}
	if (x * 4 >= win_size.x || y >= win_size.y || x < 0 || y < 0)
		return ;
	data[(y * win_size.x) + (x * 4) + 3] = (unsigned char)(color>>8 * 3);
	data[(y * win_size.x) + (x * 4) + 2] = (color % 0x1000000) >> 8 * 2;
	data[(y * win_size.x) + (x * 4) + 1] = (color % 0x1000000) >> 8;
	data[(y * win_size.x) + (x * 4) + 0] = color % 0x1000000;
}

void	string_to_image(int x, int y, int color, char *str)
{
	static void **mlx = NULL;

	if (!mlx)
		mlx = get_mlx(NULL);
	mlx_string_put(mlx[0], mlx[1], x, y, color, str);
}
