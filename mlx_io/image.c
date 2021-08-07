/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:04:17 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 11:38:11 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_io.h"

void	update_image(void)
{
	static void	**mlx = NULL;

	if (!mlx)
		mlx = get_mlx(NULL);
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
}

void	pixel_put(int x, int y, unsigned int color)
{
	static unsigned char	*data = NULL;
	static t_int_xy			wins;
	void					**mlx;
	int						n;

	if (!data)
	{
		mlx = get_mlx(NULL);
		data = (unsigned char *)mlx_get_data_addr(mlx[2], &wins.y, &wins.x, &n);
		n = wins.x;
		wins = get_window_size();
		wins.x = n;
	}
	if (x * 4 >= wins.x || y >= wins.y || x < 0 || y < 0)
		return ;
	data[(y * wins.x) + (x * 4) + 3] = (unsigned char)(color >> 8 * 3);
	data[(y * wins.x) + (x * 4) + 2] = (color % 0x1000000) >> 8 * 2;
	data[(y * wins.x) + (x * 4) + 1] = (color % 0x1000000) >> 8;
	data[(y * wins.x) + (x * 4) + 0] = color % 0x1000000;
}
