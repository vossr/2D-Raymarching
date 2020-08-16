#include "wolf.h"

double	ft_abs(double n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

int		make_fade(t_float_xy color, unsigned fade, signed xred)
{
	signed xgrn;
	signed xblu;
	signed yred;
	signed ygrn;
	signed yblu;

	if (color.x == color.y)
		return ((int)color.x);
	xred = (((int)color.x % 0x1000000) >> 4 * 4) - fade;
	xgrn = (((int)color.x % 0x10000) >> 4 * 2) - fade;
	xblu = ((int)color.x % 0x100) - fade;
	yred = (((int)color.y % 0x1000000) >> 4 * 4);
	ygrn = (((int)color.y % 0x10000) >> 4 * 2);
	yblu = ((int)color.y % 0x100);
	yred = (int)(((double)fade / 0xFF) * yred);
	ygrn = (int)(((double)fade / 0xFF) * ygrn);
	yblu = (int)(((double)fade / 0xFF) * yblu);
	xred = xred < 0 ? 0 : xred;
	xgrn = xgrn < 0 ? 0 : xgrn;
	xblu = xblu < 0 ? 0 : xblu;
	yred = yred > 0xFF ? 0xFF : yred;
	ygrn = ygrn > 0xFF ? 0xFF : ygrn;
	yblu = yblu > 0xFF ? 0xFF : yblu;
	return ((xred << 4 * 4) + (xgrn << 4 * 2) + xblu +
			(yred << 4 * 4) + (ygrn << 4 * 2) + yblu);
}

void	megapixel_put(int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			pixel_put(x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	map_print(t_float_xy location, t_float_xy direction, t_int_xy map_size, int **map)
{
	t_float_xy	color;
	int			x;
	int			y;

	color.x = 0xFF00;
	color.y = 0xFF00;
	location.x *= 8;
	location.y *= 8;
	direction.x = location.x + 20000 * direction.x;
	direction.y = location.y + 20000 * direction.y;
	print_line(location, direction, color);
	y = 0;
	while (y < map_size.y)
	{
		x = 0;
		while (x < map_size.x)
		{
			if (map[y][x] == 1)
				megapixel_put(x * 8, y * 8, 0x10FFFFFF);
			x++;
		}
		y++;
	}
}

void	print_line(t_float_xy start, t_float_xy stop, t_float_xy color)
{
	t_float_xyz	step;
	t_float_xyz	pos;
	int		i;

	i = 0;
	pos.x = start.x;
	pos.y = start.y;
	pos.z = 0;
	step.z = ft_abs(stop.x - start.x) > ft_abs(stop.y - start.y) ?
			ft_abs(stop.x - start.x) : ft_abs(stop.y - start.y);
	step.x = (stop.x - start.x) / (float)step.z;
	step.y = (stop.y - start.y) / (float)step.z;
	while (pos.z <= step.z && i < 1000)
	{
		pixel_put(pos.x, pos.y,
				make_fade(color, 0xFF * ((pos.z) / (step.z)), 0));
		pos.x += step.x;
		pos.y += step.y;
		pos.z++;
		i++;
	}
}
