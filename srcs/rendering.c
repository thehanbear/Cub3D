/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:05:07 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/11/15 05:02:56 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	draw_full_wall(t_map_data *game, t_ray *ray, mlx_texture_t *hit_texture)
{
	uint32_t	tex_y_start;
	double		tex_y_ratio;
	uint32_t	tex_x;
	uint32_t	color;
	uint32_t	y;

	tex_y_start = (ray->wall_h - game->image->height) * hit_texture->height / ray->wall_h / 2;
	tex_y_ratio = hit_texture->height / ray->wall_h;
	tex_x = hit_texture->width * ray->hit_part;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		color = get_tex_color(hit_texture, tex_x, tex_y_start + tex_y_ratio * y);
		set_image_color(game->image, (uint32_t)ray->x, y++, color);
	}
}

static void	draw_wall_with_background(t_map_data *game, t_ray *ray, mlx_texture_t *hit_texture)
{
	uint32_t	wall_y_start;
	double		tex_y_ratio;
	uint32_t	tex_x;
	uint32_t	color;
	uint32_t	y;

	wall_y_start = (SCREEN_HEIGHT - ray->wall_h) / 2;
	tex_y_ratio = hit_texture->height / ray->wall_h;
	tex_x = hit_texture->width * ray->hit_part;
	y = 0;
	while (y < wall_y_start)
		set_image_color(game->image, ray->x, y++, game->textures.ceiling);
	while (y < wall_y_start + ray->wall_h)
	{
		color = get_tex_color(hit_texture, tex_x, tex_y_ratio * (y - wall_y_start));
		set_image_color(game->image, ray->x, y++, color);
	}
	while (y < SCREEN_HEIGHT)
		set_image_color(game->image, ray->x, y++, game->textures.floor);
}

static mlx_texture_t	*get_hit_texture(t_texture *textures, t_ray *ray)
{
	ray->angle_rad = angle_norm(ray->angle_rad);
	if (ray->h_hit == false)
	{
		if (ray->angle_rad > M_PI / 2 && ray->angle_rad < 3 * (M_PI / 2))
			return (textures->w);
		else
			return (textures->e);
	}
	else
	{
		if (ray->angle_rad > 0 && ray->angle_rad < M_PI)
			return (textures->s);
		else
			return (textures->n);
	}
}

void	draw_column(t_map_data *game, t_ray *ray)
{
	mlx_texture_t	*hit_texture;

	ray->distance *= cos(angle_norm(ray->angle_rad - game->player.heading));
	ray->wall_h = (TILE_SIZE / ray->distance) * ((SCREEN_WIDTH / 2) / tan(game->player.fov_radians / 2));
	hit_texture = get_hit_texture(&game->textures, ray);
	if (ray->wall_h > SCREEN_HEIGHT)
		draw_full_wall(game, ray, hit_texture);
	else
		draw_wall_with_background(game, ray, hit_texture);
}
