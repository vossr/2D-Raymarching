/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 22:35:09 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 11:36:35 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_io.h"

static int	set_key(int call, int key)
{
	static int	*keyb = NULL;
	int			i;

	if (!keyb)
	{
		i = 0;
		keyb = (int *)malloc(sizeof(int) * 310);
		if (!keyb)
			exit(0);
		while (i < 300)
		{
			keyb[i] = 0;
			i++;
		}
	}
	if (call == 0)
		return (keyb[key]);
	else if (call == 1)
		keyb[key] = 1;
	else if (call == 2)
		keyb[key] = 0;
	return (0);
}

int	handle_keyboard_down(int key)
{
	set_key(1, key);
	wolf();
	return (0);
}

int	handle_keyboard_up(int key)
{
	set_key(2, key);
	wolf();
	return (0);
}

int	is_key_down(int key)
{
	return (set_key(0, key));
}
