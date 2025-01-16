/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:05:07 by hlee-sun          #+#    #+#             */
/*   Updated: 2025/01/16 17:47:44 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void					draw_column(t_map_data *game, t_ray *ray);
void					draw_wall_bg(t_map_data *game, t_ray *ray,
							mlx_texture_t *hit_texture);
static void				draw_wall(t_map_data *game, t_ray *ray,
							mlx_texture_t *hit_texture);
static mlx_texture_t	*get_hit_texture(t_texture *textures, t_ray *ray);

/* Draws a vertical column representing a ray hit on the screen. It calculates
   the wall height based on the distance to the hit, and determines whether
   to draw the wall and its background (ceiling/floor). */
void	draw_column(t_map_data *game, t_ray *ray)
{
	mlx_texture_t	*hit_texture;

	ray->distance *= cos(angle_norm(ray->angle_rad - game->player.heading));
	ray->wall_h = (TILE_SIZE / ray->distance) * game->camera.focal_length;
	hit_texture = get_hit_texture(&game->textures, ray);
	if (ray->wall_h >= SCREEN_HEIGHT)
		draw_wall(game, ray, hit_texture);
	else
		draw_wall_bg(game, ray, hit_texture);
}

/* Draws the background (ceiling and floor) along with the wall texture. 
   The function computes the vertical position on the texture to map onto
   the wall, then draws each pixel of the wall and background for the column.*/

void	draw_wall_bg(t_map_data *game, t_ray *ray, mlx_texture_t *hit_text)
{
	uint32_t	wall_y_start;
	double		tex_y_ratio;
	uint32_t	tex_x;
	uint32_t	color;
	uint32_t	y;

	wall_y_start = (SCREEN_HEIGHT - ray->wall_h) / 2;
	tex_y_ratio = hit_text->height / ray->wall_h;
	tex_x = hit_text->width * ray->hit_part;
	y = 0;
	while (y < wall_y_start)
		set_img_col(game->image, ray->x, y++, game->textures.ceiling);
	while (y < wall_y_start + ray->wall_h)
	{
		color = get_tex_col
			(hit_text, tex_x, tex_y_ratio * (y - wall_y_start));
		set_img_col(game->image, ray->x, y++, color);
	}
	while (y < SCREEN_HEIGHT)
		set_img_col(game->image, ray->x, y++, game->textures.floor);
}

/* Draws the wall texture on the screen for a column, calculating the vertical
   position to sample from the texture based on the wall height. */
static void	draw_wall(t_map_data *game, t_ray *ray, mlx_texture_t *hit_texture)
{
	uint32_t	tex_y_start;
	double		tex_y_ratio;
	uint32_t	tex_x;
	uint32_t	color;
	uint32_t	y;

	tex_y_ratio = hit_texture->height / ray->wall_h;
	tex_y_start = (ray->wall_h - game->image->height) * tex_y_ratio / 2;
	tex_x = hit_texture->width * ray->hit_part;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		color = get_tex_col(hit_texture, tex_x, tex_y_start + tex_y_ratio * y);
		set_img_col(game->image, (uint32_t)ray->x, y++, color);
	}
}

/* Determines which texture to use for the current ray hit based on whether
   it was a horizontal or vertical hit, and the direction of the ray. */
static mlx_texture_t	*get_hit_texture(t_texture *textures, t_ray *ray)
{
	ray->angle_rad = angle_norm(ray->angle_rad);
	if (ray->h_hit == 0)
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
