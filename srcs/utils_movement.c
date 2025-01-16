/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:47:08 by jbremser          #+#    #+#             */
/*   Updated: 2025/01/16 17:31:54 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

double	set_move_heading_x(t_map_data	*game, double move_x);
double	set_move_heading_y(t_map_data	*game, double move_y);

/* Calculates the change in the player's X position based on the movement 
   direction. Movement is adjusted by the player's heading (angle) and speed.*/
double	set_move_heading_x(t_map_data	*game, double move_x)
{
	if (game->player.moving_side == MOVE_RIGHT)
		return (move_x += -sin(game->player.heading) * PLAYER_SPEED);
	if (game->player.moving_side == MOVE_LEFT)
		return (move_x += sin(game->player.heading) * PLAYER_SPEED);
	if (game->player.moving_ahead == MOVE_FORWARD)
		return (move_x += cos(game->player.heading) * PLAYER_SPEED);
	if (game->player.moving_ahead == MOVE_BACK)
		return (move_x += -cos(game->player.heading) * PLAYER_SPEED);
	else
		return (0);
}

/* Calculates the change in the player's Y position based on the movement 
   direction. Movement is adjusted by the player's heading (angle) and speed.*/
double	set_move_heading_y(t_map_data	*game, double move_y)
{
	if (game->player.moving_side == MOVE_RIGHT)
		return (move_y += cos(game->player.heading) * PLAYER_SPEED);
	if (game->player.moving_side == MOVE_LEFT)
		return (move_y += -cos(game->player.heading) * PLAYER_SPEED);
	if (game->player.moving_ahead == MOVE_FORWARD)
		return (move_y += sin(game->player.heading) * PLAYER_SPEED);
	if (game->player.moving_ahead == MOVE_BACK)
		return (move_y += -sin(game->player.heading) * PLAYER_SPEED);
	else
		return (0);
}
