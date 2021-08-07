/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:58:42 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 08:17:58 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	size;
	size_t	i;
	size_t	j;

	i = 0;
	size = 0;
	while (dst[i])
		i++;
	while (src[size])
		size++;
	if (dstsize > i)
		size += i;
	else
		size += dstsize;
	j = 0;
	dst[i] = src[j];
	while (src[j] && i + 1 < dstsize)
	{
		i++;
		j++;
		dst[i] = src[j];
	}
	dst[i] = '\0';
	return (size);
}
