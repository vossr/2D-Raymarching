#include "wolf.h"

#ifndef LIVE_TEXTURE_H
# define LIVE_TEXTURE_H
void	update_live_texture(void);
void	init_live_texture(unsigned char **tex_ptr);
void	live_pixel_put(int texture_id, int x, int y, int color);
void	init_fdf(void);
void	init_fractal(void);
void	fdf(void);
void	fractal(void);
#endif
