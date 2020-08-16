#include "wolf.h"

int		***load_texture(void)
{
	int ***texture;
	int	i;
	int	x;
	int	y;

	texture = (int***)malloc(sizeof(int**) * 4);
	i = 0;
	while (i < 4)
	{
		texture[i] = (int**)malloc(sizeof(int*) * 64);
		y = 0;
		while (y < 64)
		{
			texture[i][y] = (int*)malloc(sizeof(int) * 64);
			x = 0;
			while (x < 64)
			{
				if (i == 0)
					texture[i][y][x] = 0xFFFFFF;
				else if (i == 1)
					texture[i][y][x] = 0xFF0000;
				else if (i == 2)
					texture[i][y][x] = 0xFF00;
				else if (y < 32 && x < 32)
					texture[i][y][x] = 0xFF0000;
				else if (y < 32)
					texture[i][y][x] = 0xFF00;
				else if (x < 32)
					texture[i][y][x] = 0xFF;
				else
					texture[i][y][x] = 0xFFFFFF;
				x++;
			}
			y++;
		}
		i++;
	}
	return (texture);
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
	static int	***texture = NULL;
	int			y;

	if (!texture)
		texture = load_texture();
	y = 0;
	while (y < line.x)
	{
		pixel_put(line_x, y, 0x7777FF);
		y++;
	}
	y = line.x;
	while (y < line.y)
	{
		pixel_put(line_x, y, texture[texture_id][(int)(64 * (((float)y - line.x) / (line.y - line.x)))][(int)(64 * texture_x)]);
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		pixel_put(line_x, y, 0x444444);
		y++;
	}
}
