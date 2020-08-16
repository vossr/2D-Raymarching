#include "wolf.h"

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

void	map_print(t_float_xy location, t_int_xy map_size, int **map)
{
	int			x;
	int			y;

	y = 0;
	while (y < map_size.y)
	{
		x = 0;
		while (x < map_size.x)
		{
			if (map[y][x] == 1)
				megapixel_put(x * 8, y * 8, 0xFFFFFF);
			else
				megapixel_put(x * 8, y * 8, 0);
			x++;
		}
		y++;
	}
	location.x *= 8;
	location.y *= 8;
	megapixel_put((int)location.x - 4, (int)location.y - 4, 0xFF00);
}

void	put_texture(int line_x, t_float_xy line, int texture_id, float texture_x)
{
	int		y;

	y = line.x;
	while (y < line.y)
	{
		if (texture_id == 0)
			pixel_put(line_x, y, texture_x * 0xFF);
		else if (texture_id == 1)
			pixel_put(line_x, y, texture_x * 0xFF);
		else if (texture_id == 2)
			pixel_put(line_x, y, texture_x * 0xFF);
		else if (texture_id == 3)
			pixel_put(line_x, y, texture_x * 0xFF);
		y++;
	}
	(void)texture_x;
}
