/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:26:32 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/11/15 04:58:22 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	angle_x(float angle)
{
	if (angle > 0 && angle < M_PI)
		return (true);
	return (false);
}

int	angle_y(float angle)
{
	if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
		return (true);
	return (false);
}

int	check_wall(float x, float y, t_map_data *game)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE);
	y_m = floor (y / TILE_SIZE);
	// if ((y_m >= game->map_rows || x_m >= game->map_cols))
	//  	return (0);
	if (game->map[y_m] && x_m <= (int)strlen(game->map[y_m]))
		if (game->map[y_m][x_m] == '1')
			return (0);
	return (1);
}
int	check_intersect_h(float angle, double *h_y, double *step_y)
{
	if (angle > 0 && angle < M_PI)
	{
		*h_y += TILE_SIZE;
		return (-1);
	}
	*step_y *= -1;
	return (1);
}

int	check_intersect_v(float angle, double *v_x, double *step_x)
{
	if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
	{
		*v_x += TILE_SIZE;
		return (-1);
	}
	*step_x *= -1;
	return (1);
}

float	h_intersect(t_map_data *game, float angle)
{
	t_vector	h;
	t_vector	step;
	t_vector	player;
	int			check;

	step.y = TILE_SIZE;
	step.x = TILE_SIZE / tan(angle);
	h.y = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
	check = check_intersect_h(angle, &h.y, &step.y);
	h.x = game->player.x + (h.y - game->player.y) / tan(angle);
	if ((angle_y(angle) && step.x > 0) || (!angle_y(angle) && step.x < 0))
		step.x *= -1;
	while (check_wall(h.x, h.y - check, game))
		h = vec_add(h, step);
	player = vec_new(game->player.x, game->player.y);
	return (vec_len(vec_sub(h, player)));
}

float	v_intersect(t_map_data *game, float angle)
{
	t_vector	v;
	t_vector	step;
	t_vector	player;
	int			check;

	step.x = TILE_SIZE; 
	step.y = TILE_SIZE * tan(angle);
	v.x = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
	check = check_intersect_v(angle, &v.x, &step.x);
	v.y = game->player.y + (v.x - game->player.x) * tan(angle);
	if ((angle_x(angle) && step.y < 0) || (!angle_x(angle) && step.y > 0))
		step.y *= -1;
	while (check_wall(v.x - check, v.y, game))
		v = vec_add(v, step);
	player = vec_new(game->player.x, game->player.y);
	return (vec_len(vec_sub(v, player)));
}

void	raycasting(t_map_data *game)
{
	t_ray		ray;
	double		h_inter;
	double		v_inter;
	int			col;

	col = 0;
	ray.angle_rad = game->player.heading - (game->player.fov_radians / 2);
	while (col < SCREEN_WIDTH)
	{
		ray.h_hit = false;
		h_inter = h_intersect(game, angle_norm(ray.angle_rad));
		v_inter = v_intersect(game, angle_norm(ray.angle_rad));
		if (v_inter <= h_inter)
			ray.distance = v_inter;
		else
		{
			ray.distance = h_inter;
			ray.h_hit = true;
		}
		draw_column(game, &ray, col);
		col++;
		ray.angle_rad += (game->player.fov_radians / SCREEN_WIDTH);
	}
}
