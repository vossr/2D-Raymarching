/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:06:11 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 08:21:19 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		tmp;
	int		i;

	if (!(*needle))
		return ((char *)haystack);
	while (len-- && *haystack)
	{
		i = 0;
		tmp = len + 1;
		while (haystack[i] == needle[i] && tmp--)
			if (!(needle[++i]))
				return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
