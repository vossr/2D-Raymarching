/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_texture.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 23:09:40 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/19 00:29:34 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIVE_TEXTURE_H
# define LIVE_TEXTURE_H
# define LIVE_TEXTURE_SIZE 120
////
#include <stdio.h>
void	init_live_texture(unsigned int **textures);
void	live_texture(t_settings *settings);
#endif
