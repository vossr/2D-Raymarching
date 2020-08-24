/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/24 15:49:30 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		buttons2(t_button *all_b, t_settings *settings)
{
	static int	click[3] = {0, 0, 0};
	int			i;

	i = -1;
	while (++i < 3)
	{
		if (handle_button(all_b[i]) || (click[i] = 0))
		{
			if ((click[i] == 2 && !is_mouse_down(1)) ||
				(click[i] == 1 && is_mouse_down(1)) ||
				(click[i] == 0 && !is_mouse_down(1)))
				click[i]++;
			else if (click[i] == 3)
			{
				all_b[i].is_on = all_b[i].is_on ? 0 : 1;
				click[i] = 0;
				if (i == 0)
					settings->fps = settings->fps ? 0 : 1;
				else if (i == 1)
					settings->print_map = settings->print_map ? 0 : 1;
				else if (i == 2)
					settings->cs_mode = settings->cs_mode ? 0 : 1;
			}
		}
	}
}

void		buttons(t_settings *settings)
{
	static t_button	*all_b = NULL;
	static int		last = 0;
	int				i;

	if (is_key_down(48))
	{
		if (!last)
			settings->menu = settings->menu ? 0 : 1;
		last = 1;
	}
	else
		last = 0;
	if (!settings->menu)
		return ;
	if (!(i = 0) && !all_b)
		all_b = init_buttons();
	buttons2(all_b, settings);
	update_image();
	i = 0;
	while (i < 3)
	{
		string_to_image(all_b[i].x + 2, all_b[i].y + 4,
			all_b[i].is_on ? 0xFF0000 : 0xFF, all_b[i].text);
		i++;
	}
}
