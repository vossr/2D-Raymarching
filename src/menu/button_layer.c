/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_layer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/20 14:44:56 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		disable_others(t_settings *s, t_button *b, int i)
{
	if (!b[i].is_on && (i == 1 || i == 3 || i == 5))
	{
		s->fov_b = 0;
		s->color_b = 0;
		s->height_b = 0;
		b[1].is_on = 0;
		b[3].is_on = 0;
		b[5].is_on = 0;
	}
}

void		reset(t_settings *s, t_button *b)
{
	int	i;

	if (s->reset_b)
	{
		s->projection_b = 0;
		s->fov_b = 0;
		s->fov = 1;
		s->spin_b = 0;
		s->color_b = 0;
		s->cycle_b = 0;
		s->height_b = 0;
		s->height = 1;
		s->height_color_b = 0;
		s->fps_b = 0;
		s->color.x = 0xFFFFFF;
		s->color.y = 0xFFFFFF;
		i = -1;
		while (++i < 9)
			b[i].is_on = 0;
	}
}

void		on_click(t_settings *s, int i, int *click)
{
	if (i == 0)
		s->projection_b = s->projection_b ? 0 : 1;
	else if (i == 1)
		s->fov_b = s->fov_b ? 0 : 1;
	else if (i == 2)
		s->spin_b = s->spin_b ? 0 : 1;
	else if (i == 3)
		s->color_b = s->color_b ? 0 : 1;
	else if (i == 4)
		s->cycle_b = s->cycle_b ? 0 : 1;
	else if (i == 5)
		s->height_b = s->height_b ? 0 : 1;
	else if (i == 6)
		s->height_color_b = s->height_color_b ? 0 : 1;
	else if (i == 7)
		s->fps_b = s->fps_b ? 0 : 1;
	else if (i == 8)
		s->reset_b = s->reset_b ? 0 : 1;
	click[i] = 0;
}

void		modify_settings(t_settings *settings)
{
	t_int_xy cursor;

	cursor = get_cursor();
	settings->active_layer = 0;
	if (cursor.x < 769 && cursor.y < 30)
		settings->active_layer = 1;
	if (settings->height_b)
		slider(&settings->height);
	if (settings->height_b && cursor.x < 250 && cursor.y < 60)
		settings->active_layer = 1;
	else if (settings->fov_b)
	{
		slider(&settings->fov);
		if (cursor.x < 250 && cursor.y < 60)
			settings->active_layer = 1;
	}
	else if (settings->color_b)
	{
		gradient(settings);
		if (cursor.x < 310 && cursor.y < 340)
			settings->active_layer = 1;
	}
	if (settings->cycle_b)
		cycle_colors(&settings->color);
}

void		button_layer(t_settings *settings)
{
	static t_button	*all_b = NULL;
	static int		click[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	int				i;

	if (!(i = 0) && !all_b)
		all_b = init_buttons();
	while (i < 9)
	{
		if (handle_button(all_b[i]) || (click[i] = 0))
		{
			if ((click[i] == 2 && !is_mouse_down(1)) ||
				(click[i] == 1 && is_mouse_down(1)) ||
				(click[i] == 0 && !is_mouse_down(1)))
				click[i]++;
			else if (click[i] == 3)
			{
				disable_others(settings, all_b, i);
				on_click(settings, i, click);
				all_b[i].is_on = all_b[i].is_on ? 0 : 1;
				reset(settings, all_b);
			}
		}
		i++;
	}
	modify_settings(settings);
}
