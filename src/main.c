/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/24 17:02:08 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	first_free_start(t_settings *settings)
{
	int x;
	int y;

	y = 0;
	while (y < settings->map_size.y)
	{
		x = 0;
		while (x < settings->map_size.x)
		{
			if (settings->map[y][x] == '0')
			{
				settings->location.x = (float)x + 0.5;
				settings->location.y = (float)y + 0.5;
				settings->direction.x = 0.0;
				settings->direction.y = 0.001;
				return ;
			}
			x++;
		}
		y++;
	}
	fatal_error("no free spawn point");
}

void	set_start_direction(t_settings *settings, int c)
{
	if (c == '^')
	{
		settings->direction.x = 0.0;
		settings->direction.y = -0.001;
	}
	else if (c == '<')
	{
		settings->direction.x = -0.001;
		settings->direction.y = 0.0;
	}
	else if (c == 'v')
	{
		settings->direction.x = 0.0;
		settings->direction.y = 0.001;
	}
	else if (c == '>')
	{
		settings->direction.x = 0.001;
		settings->direction.y = 0.0;
	}
}

void	set_start(t_settings *settings)
{
	int x;
	int y;
	int c;

	y = 0;
	while (y < settings->map_size.y)
	{
		x = 0;
		while (x < settings->map_size.x)
		{
			c = settings->map[y][x];
			if (c == '^' || c == '<' ||
					c == 'v' || c == '>')
			{
				settings->location.x = x + .5;
				settings->location.y = y + .5;
				set_start_direction(settings, c);
				return ;
			}
			x++;
		}
		y++;
	}
	first_free_start(settings);
}

void	fatal_error(char *error)
{
	ft_putstr(error);
	ft_putchar('\n');
	exit(0);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("usage: ");
		ft_putstr(argv[0]);
		ft_putstr(" [file ...]\n");
	}
	else
	{
		read_map(argv[1], NULL);
		init_window(WIN_WIDTH, WIN_HEIGHT, "Wolf3D");
	}
	return (0);
}
