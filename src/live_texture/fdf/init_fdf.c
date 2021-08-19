/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/12 20:03:32 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_errors(char *filename)
{
	int		i;
	int		fd;
	char	*line;
	char	c;

	fd = open(filename, O_RDONLY);
	if (fd < 2)
		ft_error();
	while (get_next_line(fd, &line))
	{
		if (!(i = 0) && !line)
			ft_error();
		while (line[i])
		{
			c = line[i];
			if (!(c >= '0' && c <= '9') && (c != ' ' && c != '-' && c != '+' &&
			c != 'a' && c != 'b' && c != 'c' && c != 'd' && c != 'e' &&
			c != 'f' && c != 'A' && c != 'B' && c != 'C' && c != 'D' &&
			c != 'E' && c != 'F' && c != 'x' && c != '\t' && c != ','))
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
	char	filename[] = "src/live_texture/fdf/42slope.fdf";
	int		w;
	int		h;

	check_errors(filename);
	make_map(&w, &h, filename);
}
