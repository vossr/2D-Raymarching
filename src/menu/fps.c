/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:59:13 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/19 20:02:17 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	put_fps(int fps)
{
	char			*str;

	str = NULL;
	str = ft_itoa(fps);
	string_to_image(10, WIN_HEIGHT - 30, 0xFFFF00, str);
	free(str);
	str = NULL;
}

void	fps(void)
{
	struct timeval	time;
	static long		s = 0;
	static int		i = 0;
	static int		fps = 0;

	i++;
	gettimeofday(&time, NULL);
	put_fps(fps);
	if (s != time.tv_sec)
	{
		s = time.tv_sec;
		fps = i;
		i = 0;
	}
}
