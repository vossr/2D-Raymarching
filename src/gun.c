/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/24 21:33:20 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	**load_gun(void)
{
	void	**mlx;
	void	**texture;
	int		bps;
	int		line_s;

	texture = (void**)malloc(sizeof(void*) * 4);
	mlx = get_mlx(NULL);
	texture[0] = mlx_xpm_file_to_image(mlx[0],
			"textures/wolfgun.xpm", &bps, &line_s);
	texture[1] = mlx_xpm_file_to_image(mlx[0],
			"textures/wolfgunfire.xpm", &bps, &line_s);
	texture[2] = mlx_xpm_file_to_image(mlx[0],
			"textures/flash.xpm", &bps, &line_s);
	texture[3] = mlx_xpm_file_to_image(mlx[0],
			"textures/gun.xpm", &bps, &line_s);
	if (texture[0] == NULL || texture[1] == NULL ||
			texture[2] == NULL || texture[3] == NULL)
		fatal_error("gun load fail");
	return (texture);
}

void	crosshair(void)
{
	int x;
	int y;
	int i;
	int j;

	x = WIN_WIDTH / 2;
	y = WIN_HEIGHT / 2;
	i = -1;
	while (++i < 10 && (j = -1))
		while (++j < 3)
		{
			pixel_put(x + i - 14, y + j, 0xFF00);
			pixel_put(x + i + 4, y + j, 0xFF00);
		}
	i = -1;
	while (++i < 3 && (j = -1))
		while (++j < 10)
		{
			pixel_put(x + i - 1, y + j - 14, 0xFF00);
			pixel_put(x + i - 1, y + j + 6, 0xFF00);
		}
}

void	put_gun(t_settings *settings)
{
	static void	**gun = NULL;
	static void	**mlx = NULL;
	static int	last = 0;

	if (!gun)
		gun = load_gun();
	if (!mlx)
		mlx = get_mlx(NULL);
	if (settings->cs_mode)
	{
		if (last && is_mouse_down(1) && !settings->menu)
			mlx_put_image_to_window(mlx[0], mlx[1], gun[2],
					WIN_WIDTH / 2 + 20, WIN_HEIGHT - 200 - 20);
		mlx_put_image_to_window(mlx[0], mlx[1], gun[3],
				WIN_WIDTH / 2, WIN_HEIGHT - 200);
	}
	else if (last && is_mouse_down(1) && !settings->menu)
		mlx_put_image_to_window(mlx[0], mlx[1], gun[1],
				WIN_WIDTH / 2 - (800 / 2), WIN_HEIGHT - 800);
	else
		mlx_put_image_to_window(mlx[0], mlx[1], gun[0],
				WIN_WIDTH / 2 - (800 / 2), WIN_HEIGHT - 800);
	last = is_mouse_down(1) ? 0 : 1;
}

void	capture_cursor(t_settings *settings)
{
	UInt32		dispid;
	CGPoint		cursor;
	static int	last_menu_state = 1;

	//if lose focus menu = 1;
	//CGAssociateMouseAndMouseCursorPosition(0);
	dispid = CGMainDisplayID();
	cursor.x = 700;
	cursor.y = 700;
	//move releative to window;
	if (!settings->menu)
		CGWarpMouseCursorPosition(cursor);
	if (last_menu_state != settings->menu)
	{
		if (!settings->menu)
			CGDisplayHideCursor(dispid);
		else
		{
			CGDisplayShowCursor(dispid);
			CGDisplayMoveCursorToPoint(dispid, cursor);
		}
	}
	last_menu_state = settings->menu;
}
