/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:26:19 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 08:16:26 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int		neg;
	int		res;

	res = 0;
	neg = 1;
	while (*str && ((*str > 7 && *str < 14) || *str == 32))
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str <= '9' && *str >= '0' && *str)
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	return (res * neg);
}
