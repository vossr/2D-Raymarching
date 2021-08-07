/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 22:52:45 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 09:05:27 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFF_SIZE 1000
#define MAXFD_SIZE 100

char	*ft_join(char *s1, char *s2, char **as, int i)
{
	char	*fresh;
	int		j;

	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	fresh = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!fresh)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j] != '\0')
		fresh[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j] != '\0')
		fresh[i++] = s2[j++];
	fresh[i] = '\0';
	if (as)
		free(*as);
	if (as)
		*as = NULL;
	return (fresh);
}

int	ft_set_value(char **line, char *tmp, size_t size)
{
	size_t	line_size;

	line_size = 0;
	if (!tmp)
		return (0);
	*line = (char *)malloc(sizeof(char) * (size + 1));
	if (!(*line))
		return (0);
	while (line_size < size)
	{
		(*line)[line_size] = tmp[line_size];
		line_size++;
	}
	(*line)[line_size] = '\0';
	return (1);
}

int	ft_make_line(char **line, char **tmp, int fd, int res)
{
	char	*tmp2;
	size_t	line_size;

	line_size = 0;
	while (tmp[fd][line_size] != '\n' && tmp[fd][line_size])
		line_size++;
	if (tmp[fd][line_size] == '\n')
	{
		ft_set_value(line, tmp[fd], line_size);
		tmp2 = ft_join(tmp[fd] + line_size + 1, NULL, &tmp[fd], 0);
		free(tmp[fd]);
		tmp[fd] = tmp2;
		return (1);
	}
	if (res == BUFF_SIZE)
		return (get_next_line(fd, line));
	*line = ft_join(tmp[fd], NULL, &tmp[fd], 0);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*tmp[MAXFD_SIZE];
	char		buff[BUFF_SIZE + 1];
	char		*tmp2;
	int			res;
	int			i;

	i = 0;
	if (fd < 0 || !line)
		return (-1);
	while (0 < (res = read(fd, buff, BUFF_SIZE)))
	{
		if ((buff[res] = '\0') && tmp[fd] == NULL)
			if ((tmp[fd] = (char *)malloc(sizeof(char) * 2)))
				if (!(tmp[fd][0] = 0))
					tmp[fd][1] = '\0';
		tmp2 = ft_join(tmp[fd], buff, NULL, 0);
		free(tmp[fd]);
		tmp[fd] = tmp2;
		while (buff[i])
			if (buff[i++] == '\n')
				break ;
	}
	if ((res < 0) || (!res && (!tmp[fd] || !tmp[fd][0])))
		return (res);
	return (ft_make_line(line, tmp, fd, res));
}
