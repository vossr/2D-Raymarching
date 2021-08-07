/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:22:24 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 09:02:34 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*fresh;

	fresh = (char *)malloc(sizeof(fresh) * (size));
	if (!fresh)
		return (NULL);
	while (size--)
		fresh[size] = 0;
	return ((void *)fresh);
}
