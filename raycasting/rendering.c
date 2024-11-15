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

#include "raycasting.h"

float	angle_norm(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

void	draw_background(t_game *game, int col, int t_pix, int b_pix)
{
	int		i;

	i = b_pix;
	while (i < SCREEN_HEIGHT)
		mlx_put_pixel(game->image, col, i++, COLOR_FLOOR);
	i = 0;
	while (i < t_pix)
		mlx_put_pixel(game->image, col, i++, COLOR_CEILING);
}

int	get_wall_color(t_ray *ray)
{
	ray->angle_rad = angle_norm(ray->angle_rad);
	if (ray->h_hit == false)
	{
		if (ray->angle_rad > M_PI / 2 && ray->angle_rad < 3 * (M_PI / 2))
			return (COLOR_WALL_W);
		else
			return (COLOR_WALL_E);
	}
	else
	{
		if (ray->angle_rad > 0 && ray->angle_rad < M_PI)
			return (COLOR_WALL_S);
		else
			return (COLOR_WALL_N);
	}
}

void	draw_column(t_game *game, t_ray *ray, int col)
{
	double	wall_h;
	double	bottom;
	double	top;
	int		color;

	ray->distance *= cos(angle_norm(ray->angle_rad - game->player.heading));
	wall_h = (TILE_SIZE / ray->distance) * ((SCREEN_WIDTH / 2) / tan(game->player.fov_radians / 2));
	bottom = (SCREEN_HEIGHT / 2) + (wall_h / 2);
	top = (SCREEN_HEIGHT / 2) - (wall_h / 2);
	if (bottom > SCREEN_HEIGHT)
		bottom = SCREEN_HEIGHT;
	if (top < 0)
		top = 0;
	draw_background(game, col, top, bottom);
	color = get_wall_color(ray);
	while (top < bottom)
		mlx_put_pixel(game->image, col, top++, color);
}
