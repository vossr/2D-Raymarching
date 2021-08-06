/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/06 14:08:26 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

float		deg_to_rad(float d)
{
	return (d * (M_PI / 180));
}

static void		collision(t_float_xy *location, float angle,
												int neg, char **map)
{
	t_int_xy	loc_on_map_f;
	int			speed;
	t_float_xy direction;

	direction.x = sinf(deg_to_rad(angle)) / RAY_PREC;
	direction.y = cosf(deg_to_rad(angle)) / RAY_PREC;

	speed = 40;
	loc_on_map_f.y = map[(int)(location->y + neg * direction.y * speed)]
							[(int)location->x];
	loc_on_map_f.x = map[(int)location->y]
							[(int)(location->x + neg * direction.x * speed)];
	if (1 != loc_on_map_f.x)
		location->x += direction.x * speed * neg;
	if (1 != loc_on_map_f.y)
		location->y += direction.y * speed * neg;
}

static void	player_movement(t_settings *settings)
{
	int		fwd;
	int		bwd;

	if (is_key_down(124))
		settings->angle -= 2;
	if (is_key_down(123))
		settings->angle += 2;
	fwd = is_key_down(126) + is_key_down(13);
	bwd = is_key_down(125) + is_key_down(1);
	if (fwd)
		collision(&settings->location, settings->angle, 1, settings->map);
	if (bwd)
		collision(&settings->location, settings->angle, -1, settings->map);
	if (is_key_down(0))
		collision(&settings->location, settings->angle + 90 , 1, settings->map);
	if (is_key_down(2))
		collision(&settings->location, settings->angle + 90 , -1, settings->map);
}

int			wolf(void)
{
	static t_settings *settings = NULL;

	if (!settings)
		settings = read_map(NULL);
	if (is_key_down(53))
		exit(0);
	player_movement(settings);
	raycast(settings);
	update_image();
	return (0);
}
