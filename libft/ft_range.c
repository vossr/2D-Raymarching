/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 11:48:24 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 08:57:53 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range(int min, int max)
{
	int	*res;
	int	i;

	i = 0;
	if (min >= max)
		return (0);
	while (i < max - min)
		i++;
	res = (int *)malloc(1 + i * sizeof(int));
	if (!res)
		return (0);
	i = 0;
	while (min < max)
		res[i++] = min++;
	return (res);
}
