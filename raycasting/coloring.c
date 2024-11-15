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

#include "raycasting.h"

// 텍스처에서 색상을 가져오는 함수
uint32_t get_tex_color(mlx_texture_t *tex, uint32_t x, uint32_t y)
{
    uint32_t *pixel;

    if (!tex || x >= tex->width || y >= tex->height)
        return (0);
    pixel = (uint32_t *)tex->pixels;
    return (pixel[y * tex->width + x]);
}

// 이미지에 픽셀 색상을 설정하는 함수
void set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
    uint32_t *pixel;

    if (!img || x >= img->width || y >= img->height)
        return;
    pixel = (uint32_t *)img->pixels;
    pixel[y * img->width + x] = color;
}

// RGBA 값으로 색상을 합성하는 함수
uint32_t rgba(int r, int g, int b, int a)
{
    return (a << 24 | b << 16 | g << 8 | r);
}

uint32_t hex_to_int(const char *hex)
{
    uint32_t color = 0;
    if (hex[0] == '#')
        hex++;  // '#' 기호를 건너뜁니다.
    
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