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
