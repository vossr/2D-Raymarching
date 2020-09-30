#include "wolf.h"

void	live_pixel_put_texture(int texture_id, int x, int y, int color, unsigned char **tex_ptr)
{
	static unsigned char	**texture;

	if (tex_ptr)
	{
		texture = tex_ptr;
		return ;
	}
	y *= 512 * 4;
	x *= 4;
	texture[texture_id][y + x + 3] = (unsigned char)(color>>8 * 3);
	texture[texture_id][y + x + 2] = (color % 0x1000000) >> 8 * 2;
	texture[texture_id][y + x + 1] = (color % 0x1000000) >> 8;
	texture[texture_id][y + x + 0] = color % 0x1000000;
}

void	init_live_texture(unsigned char **tex_ptr)
{
	live_pixel_put_texture(0, 0, 0, 0, tex_ptr);
	init_fdf();
	init_fractal();
}

void	live_pixel_put(int texture_id, int x, int y, int color)
{
	if (x >= 512 || y >= 512 || x < 0 || y < 0)
		return ;
	live_pixel_put_texture(texture_id, x, y, color, NULL);
}
/*
void	fdf(void)
{
	static int				i = 0;
	static int				which = 0;

	i++;
	if (i > 50)
	{
		i = 0;
		which = which ? 0 : 1;
	}
	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 64; x++)
		{
			if (which)
				live_pixel_put(x, y, 0xFF0000);
			else
				live_pixel_put(x, y, 0xFF);
		}
	}
}
*/
void	update_live_texture(void)
{
	fractal();
	fdf();
}
