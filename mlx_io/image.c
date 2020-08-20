/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:04:17 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/20 13:10:54 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_io.h"

void	update_image(void)
{
	static void **mlx = NULL;

	if (!mlx)
		mlx = get_mlx(NULL);
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
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
	int red = ((color << 8 * 1) >> 8 * 3) * (color >> 8 * 3);
	red += data[(y * win_size.x) + (x * 4) + 2];
	if (red > 255)
		red = 255;
	if (red < 0)
		red = 0;
	data[(y * win_size.x) + (x * 4) + 2] = (char)red;
	int grn = ((color << 8 * 2) >> 8 * 3) * (color >> 8 * 3);
	grn += data[(y * win_size.x) + (x * 4) + 1];
	if (grn > 255)
		grn = 255;
	if (grn < 0)
		grn = 0;
	data[(y * win_size.x) + (x * 4) + 1] = (char)grn;
	int blu = ((color << 8 * 3) >> 8 * 3) * (color >> 8 * 3);
	blu += data[(y * win_size.x) + (x * 4) + 0];
	if (blu > 255)
		blu = 255;
	if (blu < 0)
		blu = 0;
	data[(y * win_size.x) + (x * 4) + 0] = (char)blu;
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
