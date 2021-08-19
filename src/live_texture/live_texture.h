/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_texture.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 23:09:40 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/19 20:25:54 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIVE_TEXTURE_H
# define LIVE_TEXTURE_H
# define LIVE_TEXTURE_SIZE 512
# include "wolf.h"
void	init_live_texture(unsigned int **textures);
void	live_texture(t_settings *settings);
void	live_pixel_put(int color, int x, int y,
			unsigned int **get_textures);
void	frame_in_frame(void);
#endif
