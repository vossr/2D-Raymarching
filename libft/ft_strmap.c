/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:28:58 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 08:45:45 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		size;
	char	*fresh;

	size = 0;
	if (!s)
		return (0);
	while (s[size])
		size++;
	fresh = (char *)malloc(sizeof(fresh) * (size + 1));
	if (!fresh)
		return (NULL);
	fresh[size] = '\0';
	size = 0;
	while (*s)
	{
		fresh[size] = f(*s);
		s++;
		size++;
	}
	return (fresh);
}
