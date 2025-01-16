/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:26:32 by hlee-sun          #+#    #+#             */
/*   Updated: 2025/01/16 17:24:39 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static float	h_hit(t_map_data *game, float angle);
static float	v_hit(t_map_data *game, float angle);
static void		get_hit_part(t_map_data *game, t_ray *ray);
void			raycasting(t_map_data *game);

/* Calculates the horizontal hit distance from the player's position based
   on the current angle. This function checks the direction of the ray and
   iterates through the map until it hits a wall, returning the distance to
   the hit point. */
static float	h_hit(t_map_data *game, float angle)
{
	t_vector	h;
	int			check;

	game->step = vec_from_angle(angle);
	if (game->step.y == 0)
		return (-1);
	game->step = vec_mul(game->step, TILE_SIZE / game->step.y);
	if ((x_r(angle) && game->step.x < 0) || (!x_r(angle) && game->step.x > 0))
		game->step.x *= -1;
	h.y = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
	if (y_r(angle))
	{
		h.y += TILE_SIZE;
		check = 1;
	}
	else
	{
		game->step.y *= -1;
		check = -1;
	}
	h.x = game->player.x + (h.y - game->player.y) / tan(angle);
	while (check_wall(h.x, h.y + check, game))
		h = vec_add(h, game->step);
	game->vector_player = vec_new(game->player.x, game->player.y);
	return (vec_len(vec_sub(h, game->vector_player)));
}

/* Calculates the vertical hit distance from the player's position based on
   the current angle. Similar to `h_hit`, this function traces the ray in the
   vertical direction and returns the distance to the first wall hit. */
static float	v_hit(t_map_data *game, float angle)
{
	t_vector	v;
	int			check;

	game->step = vec_from_angle(angle);
	if (game->step.x == 0)
		return (-1);
	game->step = vec_mul(game->step, TILE_SIZE / game->step.x);
	if ((y_r(angle) && game->step.y < 0) || (!y_r(angle) && game->step.y > 0))
		game->step.y *= -1;
	v.x = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
	if (x_r(angle))
	{
		v.x += TILE_SIZE;
		check = 1;
	}
	else
	{
		game->step.x *= -1;
		check = -1;
	}
	v.y = game->player.y + (v.x - game->player.x) * tan(angle);
	while (check_wall(v.x + check, v.y, game))
		v = vec_add(v, game->step);
	game->vector_player = vec_new(game->player.x, game->player.y);
	return (vec_len(vec_sub(v, game->vector_player)));
}

/* Calculates the hit part on the tile (i.e., the exact position on the
   tile where the ray hit). It updates the `hit_part` of the ray based on
   whether the horizontal or vertical hit was encountered. */
static void	get_hit_part(t_map_data *game, t_ray *ray)
{
	t_vector	v;

	v = vec_from_angle(ray->angle_rad);
	v = vec_mul(v, ray->distance);
	if (ray->h_hit)
		ray->hit_part = (game->player.x + v.x) / (double)TILE_SIZE;
	else
		ray->hit_part = (game->player.y + v.y) / (double)TILE_SIZE;
	ray->hit_part = ray->hit_part - floor(ray->hit_part);
}

/* Performs the raycasting loop. For each vertical line of pixels on the screen,
   it casts rays to calculate the distance to the nearest wall. It compares
   horizontal and vertical hit distances, determines the closest hit, and
   then draws the column representing the ray's hit in the window. */
void	raycasting(t_map_data *game)
{
	t_ray		ray;
	double		h_distance;
	double		v_distance;
	uint32_t	x;

	x = 0;
	ray.angle_rad = game->player.heading - (game->camera.fov_radians / 2);
	while (x < SCREEN_WIDTH)
	{
		ray.x = x;
		ray.h_hit = 0;
		h_distance = h_hit(game, angle_norm(ray.angle_rad));
		v_distance = v_hit(game, angle_norm(ray.angle_rad));
		if (h_distance == -1 || (v_distance != -1 && v_distance <= h_distance))
			ray.distance = v_distance;
		else
		{
			ray.distance = h_distance;
			ray.h_hit = 1;
		}
		get_hit_part(game, &ray);
		draw_column(game, &ray);
		x++;
		ray.angle_rad += game->camera.angle_increment;
	}
}
