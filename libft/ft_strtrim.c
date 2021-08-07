/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:59:36 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 08:49:50 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*fresh;
	int		size;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	size = ft_strlen(s);
	size--;
	while (i < size && (s[size] == ' ' || s[size] == '\n' || s[size] == '\t'))
		size--;
	size++;
	if (!i)
		return (ft_strdup(s));
	size -= i;
	fresh = (char *)malloc(sizeof(char) * (size + 1));
	if (!fresh)
		return (NULL);
	fresh[size] = '\0';
	while (size--)
		fresh[size] = s[size + i];
	return (fresh);
}
