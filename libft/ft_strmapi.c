/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:36:33 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 08:46:21 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			size;
	char			*fresh;

	if (!s)
		return (0);
	size = 0;
	while (s[size])
		size++;
	fresh = (char *)malloc(sizeof(fresh) * (size));
	if (!fresh)
		return (NULL);
	fresh[size] = '\0';
	size = 0;
	while (*s)
	{
		fresh[size] = f(size, *s);
		s++;
		size++;
	}
	return (fresh);
}
