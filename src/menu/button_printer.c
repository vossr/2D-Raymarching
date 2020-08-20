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

void		print_button_text(t_xyz color, int text_color, t_button b)
{
	t_xyz	start;
	t_xyz	stop;
	t_xyz	edge;
	int		i;

	i = 0;
	start.x = b.x;
	start.y = 0;
	stop.x = b.x + b.size_x;
	stop.y = 0;
	edge.x = 0x555555;
	edge.y = 0x555555;
	color.y = color.x;
	while (i < 30)
	{
		if (!i || i == 29)
			print_line(start, stop, edge);
		else
			print_line(start, stop, color);
		start.y++;
		stop.y++;
		i++;
	}
	string_to_image(b.x + 2, 4, text_color, b.text);
}

int			handle_button(t_button b)
{
	int			text_color;
	t_int_xy	cursor;
	t_xyz		color;
	int			res;

	res = 0;
	color.x = 0xaeacad;
	cursor = get_cursor();
	if (b.is_on)
		color.x = 0x2755b2;
	text_color = b.is_on ? 0xFFFFFFF : 0;
	if (cursor.x > b.x && cursor.x < b.x + b.size_x &&
	cursor.y > 0 && cursor.y < 30)
	{
		res++;
		color.x = 0x807e7f;
		text_color = 0x707070;
		if (is_mouse_down(1))
			color.x = 0x2755b2;
		if (is_mouse_down(1))
			res++;
	}
	print_button_text(color, text_color, b);
	return (res);
}

void		set_button_text(t_button *b, int i)
{
	if (!(b->text = (char*)malloc(sizeof(char) * 20)))
		ft_error();
	if (i == 0)
		ft_strcpy(b->text, "projection");
	else if (i == 1)
		ft_strcpy(b->text, "fov");
	else if (i == 2)
		ft_strcpy(b->text, "spin");
	else if (i == 3)
		ft_strcpy(b->text, "color");
	else if (i == 4)
		ft_strcpy(b->text, "cycle colors");
	else if (i == 5)
		ft_strcpy(b->text, "height");
	else if (i == 6)
		ft_strcpy(b->text, "height coloring");
	else if (i == 7)
		ft_strcpy(b->text, "fps");
	else if (i == 8)
		ft_strcpy(b->text, "reset");
}

t_button	*init_buttons(void)
{
	t_button	*all_b;
	int			x;
	int			i;

	if (!(all_b = (t_button*)malloc(sizeof(t_button) * 9)))
		ft_error();
	x = 0;
	i = 0;
	while (i < 9)
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
