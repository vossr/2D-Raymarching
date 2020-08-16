#include "wolf.h"

double	ft_abs(double n)
{
	if (n < 0)
		return (n * -1);
	return (n);
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
	int			x;
	int			y;

	location.x *= 8;
	location.y *= 8;
	direction.x = location.x + 20000 * direction.x;
	direction.y = location.y + 20000 * direction.y;
	print_line(location, direction, 0xFF00);
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

void	print_line(t_float_xy start, t_float_xy stop, int color)
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
		pixel_put(pos.x, pos.y, color);
		pos.x += step.x;
		pos.y += step.y;
		pos.z++;
		i++;
	}
}
