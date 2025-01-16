/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:53:40 by jbremser          #+#    #+#             */
/*   Updated: 2025/01/16 17:33:11 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

float	angle_norm(float angle);
int		y_r(float angle);
int		x_r(float angle);
int		check_wall(float x, float y, t_map_data *game);

/* Normalizes an angle to stay within the range [0, 2 * PI]. 
   If the angle is negative, it adds 2 * PI; if it exceeds 2 * PI, 
   it subtracts 2 * PI. */
float	angle_norm(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

/* Determines if the given angle is in the range for vertical ray directions
   (i.e., between 0 and PI). */
int	y_r(float angle)
{
	if (angle > 0 && angle < M_PI)
		return (1);
	return (0);
}

/* Determines if the given angle is in the range for horizontal ray directions
   (i.e., between 0 and PI/2 or between 3 * PI/2 and 2 * PI). */
int	x_r(float angle)
{
	if (angle < (M_PI / 2) || angle > (3 * M_PI) / 2)
		return (1);
	return (0);
}

/* Checks whether the given coordinates(x, y)are colliding with wall on the map.
   The function checks if the coordinates are within bounds, and if the map at
   that position contains a wall ('1'). */
int	check_wall(float x, float y, t_map_data *game)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE);
	y_m = floor (y / TILE_SIZE);
	if (y_m >= game->map_rows || !game->map[y_m]
		|| x_m >= (int)strlen(game->map[y_m]) || !game->map[y_m][x_m]
		|| game->map[y_m][x_m] == '1')
		return (0);
	return (1);
}
