/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/20 18:19:00 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_errors(char *filename, int i)
{
	int		fd;
	char	*line;
	char	c;

	fd = open(filename, O_RDONLY);
	if (fd < 2)
		ft_error();
	while (get_next_line(fd, &line))
	{
		i = 0;
		if (!line)
			ft_error();
		while (line[i])
		{
			c = line[i];
			if (!(c >= '0' && c <= '9') && (c != ' ' && c != '-' && c != ','
					&& c != 'a' && c != 'b' && c != 'c' && c != 'd' && c != 'e'
					&& c != 'f' && c != 'A' && c != 'B' && c != 'C' && c != 'D'
					&& c != 'E' && c != 'F' && c != 'x' && c != '\t'))
				ft_error();
			i++;
		}
		free(line);
	}
}

void	ft_error(void)
{
	ft_putstr("error\n");
	exit(0);
}

void	init_fdf(void)
{
	int		w;
	int		h;

	check_errors("src/live_texture/fdf/42slope.fdf", 0);
	make_map(&w, &h, "src/live_texture/fdf/42slope.fdf");
}
