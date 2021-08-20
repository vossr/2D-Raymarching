/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:06:50 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/20 17:31:27 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_map_len(int n)
{
	static int	len = 0;

	if (!n)
		return (len);
	len = n;
	return (0);
}

int	get_map_width(int n)
{
	static int	len = 0;

	if (!n)
		return (len);
	len = n;
	return (0);
}

int	get_height(char *filename)
{
	char		*line;
	int			fd;
	static int	height = 0;

	if (height != 0)
	{
		if (height * 50 < 500)
			return (500);
		else if (height * 50 > 1200)
			return (1200);
		else
			return (height * 50);
	}
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		free(line);
		height++;
	}
	close(fd);
	return (height);
}

int	get_width(char *filename, int i)
{
	char		*line;
	static int	width = 0;

	if (width != 0)
	{
		if (width * 50 < 768)
			return (768);
		else if (width * 50 > 2000)
			return (2000);
		return (width * 50);
	}
	i = open(filename, O_RDONLY);
	get_next_line(i, &line);
	i = 0;
	while (line[i])
	{
		if (line[i + 1] || line[i] != ' ')
			width++;
		while (line[i] && line[i] == ' ')
			i++;
		while (line[i] && line[i] != ' ')
			i++;
	}
	free(line);
	return (width);
}

t_xyz	*make_map(int *width, int *height, char *filename)
{
	static t_xyz	*map = NULL;
	int				fd;

	if (map)
		return (map);
	*width = get_width(filename, 0);
	*height = get_height(filename);
	if ((*width == 1 && *height == 1) || (*width > 5 && *height == 1)
		|| (*width == 1 && *height == 1) || (*width == 1 && *height > 5))
		ft_error();
	map = (t_xyz *)malloc(sizeof(t_xyz) * (*width * *height));
	if (!map)
		ft_error();
	fd = open(filename, O_RDONLY);
	get_map_len(*width * *height);
	get_map_width(*width);
	fdf_set_map(map, fd, *width, get_map_len(0) / *width / 2);
	close(fd);
	*width = get_width(filename, 0);
	*height = get_height(filename);
	return (map);
}
