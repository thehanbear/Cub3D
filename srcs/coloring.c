/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:32:42 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/11/14 15:42:22 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

uint32_t get_tex_color(mlx_texture_t *tex, uint32_t x, uint32_t y)
{
    uint32_t *pixel;

    if (!tex || x >= tex->width || y >= tex->height)
        return (0);
    pixel = (uint32_t *)tex->pixels;
    return (pixel[y * tex->width + x]);
}

void set_image_color(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
    uint32_t *pixel;

    if (!img || x >= img->width || y >= img->height)
        return;
    pixel = (uint32_t *)img->pixels;
    pixel[y * img->width + x] = color;
}

uint32_t rgba(int r, int g, int b, int a)
{
	return (a << 24 | b << 16 | g << 8 | r);
}
