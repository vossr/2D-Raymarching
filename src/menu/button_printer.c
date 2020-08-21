/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_layer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/20 14:45:04 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		horizontal_line(int y, int x, int size, int color)
{
	int asd;

	asd = 0;
	while (asd < size)
	{
		pixel_put(x + asd, y, color);
		asd++;
	}
}

void		print_button(int color, int text_color, t_button b)
{
(void)text_color;
(void)color;
	t_int_xy	start;
	t_int_xy	stop;
	int		i;

	i = 0;
	start.x = b.x;
	start.y = 0;
	stop.x = b.x + b.size_x;
	stop.y = 0;
	while (i < 30)
	{
		if (!i || i == 29)
			horizontal_line(start.y, start.x, stop.x - start.x, 0x555555);
		else
			horizontal_line(start.y, start.x, stop.x - start.x, color);
		start.y++;
		stop.y++;
		i++;
	}
}

int			handle_button(t_button b)
{
	int			text_color;
	t_int_xy	cursor;
	int			color;
	int			res;

	res = 0;
	color = 0xaeacad;
	cursor = get_cursor();
	if (b.is_on)
		color = 0x2755b2;
	text_color = b.is_on ? 0xFFFFFFF : 0;
	if (cursor.x > b.x && cursor.x < b.x + b.size_x &&
	cursor.y > 0 && cursor.y < 30)
	{
		res++;
		color = 0x807e7f;
		text_color = 0x707070;
		if (is_mouse_down(1))
			color = 0x2755b2;
		if (is_mouse_down(1))
			res++;
	}
		text_color = 0xFF0000;
	print_button(color, text_color, b);
	return (res);
}

void		set_button_text(t_button *b, int i)
{
	if (!(b->text = (char*)malloc(sizeof(char) * 20)))
		;
		//ft_error();
	if (i == 0)
		ft_strcpy(b->text, "fps");
	else if (i == 1)
		ft_strcpy(b->text, "minimap");
	else if (i == 2)
		ft_strcpy(b->text, "Counter-Strike mode");
}

t_button	*init_buttons(void)
{
	t_button	*all_b;
	int			x;
	int			i;

	if (!(all_b = (t_button*)malloc(sizeof(t_button) * 3)))
		;
		//ft_error();
	x = 0;
	i = 0;
	while (i < 3)
	{
		all_b[i].x = x;
		all_b[i].is_on = 0;
		set_button_text(&all_b[i], i);
		all_b[i].size_x = ft_strlen(all_b[i].text) * 12;
		x += all_b[i].size_x + 1;
		i++;
	}
	return (all_b);
}
