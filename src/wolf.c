/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 12:07:52 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180));
}

static void	collision(t_vec2 *location, double angle,
									int neg, char **map)
{
	t_int_xy	loc_on_map_f;
	t_vec2		dir;

	dir.x = sin(deg_to_rad(angle)) * PLAYER_SPEED;
	dir.y = cos(deg_to_rad(angle)) * PLAYER_SPEED;
	loc_on_map_f.y = map[(int)(location->y + neg * dir.y)][(int)location->x];
	loc_on_map_f.x = map[(int)location->y][(int)(location->x + neg * dir.x)];
	if (1 != loc_on_map_f.x)
		location->x += dir.x * neg;
	if (1 != loc_on_map_f.y)
		location->y += dir.y * neg;
}

static void	player_movement(t_settings *set)
{
	int		fwd;
	int		bwd;

	if (is_key_down(124))
		set->angle -= 2;
	if (is_key_down(123))
		set->angle += 2;
	fwd = is_key_down(126) + is_key_down(13);
	bwd = is_key_down(125) + is_key_down(1);
	if (fwd)
		collision(&set->location, set->angle, 1, set->map);
	if (bwd)
		collision(&set->location, set->angle, -1, set->map);
	if (is_key_down(0))
		collision(&set->location, set->angle + 90, 1, set->map);
	if (is_key_down(2))
		collision(&set->location, set->angle + 90, -1, set->map);
}

int	wolf(void)
{
	static t_settings	*settings = NULL;

	if (!settings)
		settings = init(NULL);
	if (is_key_down(53))
		exit(0);
	player_movement(settings);
	raycast(settings);
	update_image();
	return (0);
}
