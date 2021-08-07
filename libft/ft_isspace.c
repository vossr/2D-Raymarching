/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:05:56 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 07:40:19 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	if ((c == '\t') || (c == '\n') || (c == '\v'))
		return (1);
	return ((c == '\f') || (c == '\r') || (c == ' '));
}
