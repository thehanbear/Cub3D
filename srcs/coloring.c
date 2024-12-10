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

static int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

uint32_t get_tex_color(mlx_texture_t *tex, uint32_t x, uint32_t y)
{
    uint32_t *pixel;

    if (!tex || x >= tex->width || y >= tex->height)
        return (0);
    pixel = (uint32_t *)tex->pixels;
    return (reverse_bytes(pixel[y * tex->width + x]));
}

void set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
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

uint32_t hex_to_int(const char *hex)
{
    uint32_t color = 0;
    if (hex[0] == '#')
        hex++;
    
    for (int i = 0; hex[i] != '\0'; i++)
    {
        color = color * 16;
        if (hex[i] >= '0' && hex[i] <= '9')
            color += hex[i] - '0';
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            color += hex[i] - 'A' + 10;
        else if (hex[i] >= 'a' && hex[i] <= 'f')
            color += hex[i] - 'a' + 10;
    }
    return color;
}