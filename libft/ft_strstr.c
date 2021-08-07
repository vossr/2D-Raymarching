/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 20:26:00 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 08:51:17 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;

	if (!(*needle))
		return ((char *)haystack);
	while (*haystack)
	{
		if (*haystack == needle[0])
		{
			i = 0;
			j = 0;
			while (haystack[i++] == needle[j++])
				if (!(needle[j]))
					return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
