/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/15 13:22:41 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		put_usage(char *arg)
{
	ft_putstr("usage: ");
	ft_putstr(arg);
	ft_putstr(" [file ...]\n");
}

int			main(int argc, char **argv)
{
	if (argc != 2)
		put_usage(argv[0]);
	init_window(1280, 720, "Wolf3D");
	return (0);
}
