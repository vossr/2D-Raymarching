/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 23:09:47 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/18 23:36:50 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_live_texture(unsigned int **textures)
{
	int	i;

	i = 4;
	while (i < 8)
	{
		textures[i] = (unsigned int *)malloc(sizeof(unsigned int)
				* LIVE_TEXTURE_SIZE * LIVE_TEXTURE_SIZE);
		i++;
	}
}
