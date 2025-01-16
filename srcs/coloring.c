/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:32:42 by hlee-sun          #+#    #+#             */
/*   Updated: 2025/01/16 17:03:25 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

uint32_t	get_tex_col(mlx_texture_t *tex, uint32_t x, uint32_t y);
void		set_img_col(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t col);
uint32_t	rgba(int r, int g, int b, int a);

/* Retrieves the color of a specific pixel from the texture `tex` at
coordinates (x, y). Returns the color as a uint32_t value, or 0 if 
the coordinates are out of bounds or the texture is invalid. */
uint32_t	get_tex_col(mlx_texture_t *tex, uint32_t x, uint32_t y)
{
	uint32_t	*pixel;

	if (!tex || x >= tex->width || y >= tex->height)
		return (0);
	pixel = (uint32_t *)tex->pixels;
	return (pixel[y * tex->width + x]);
}

/* Sets the color of a specific pixel in the image `img` at coordinates (x, y)
   to the specified `color`. If the coordinates are out of bounds or the image
   is invalid, the function does nothing. */
void	set_img_col(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t col)
{
	uint32_t	*pixel;

	if (!img || x >= img->width || y >= img->height)
		return ;
	pixel = (uint32_t *)img->pixels;
	pixel[y * img->width + x] = col;
}

/* Constructs a 32-bit RGBA color value from individual red, green, blue,
   and alpha components. The function returns the resulting color in the
   format (A << 24 | B << 16 | G << 8 | R). */
uint32_t	rgba(int r, int g, int b, int a)
{
	return (a << 24 | b << 16 | g << 8 | r);
}
