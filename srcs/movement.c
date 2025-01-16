/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:12:31 by hlee-sun          #+#    #+#             */
/*   Updated: 2025/01/16 17:21:02 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void		player_loop(void *param);
static void	rotate_player(t_player *player);
static void	move_player(t_map_data *game, double move_x, double move_y);
void		handle_movement_pressed(mlx_key_data_t keydata, t_map_data *game);
void		handle_movement_released(mlx_key_data_t keydata, t_map_data *game);

/* Handles player movement and rotation during each game loop iteration.
   If the player is rotating, their orientation is updated. If the player
   is moving forward or sideways, their position is updated accordingly. */
void	player_loop(void *param)
{
	double		move_x;
	double		move_y;
	t_map_data	*game;

	game = param;
	if (game->player.rotating != 0)
		rotate_player(&(game->player));
	if (game->player.moving_ahead != 0 || game->player.moving_side != 0)
	{
		move_x = 0;
		move_y = 0;
		move_x = set_move_heading_x(game, move_x);
		move_y = set_move_heading_y(game, move_y);
		move_player(game, move_x, move_y);
	}
}

/* Rotates the player based on their current rotation state. The player's
   heading is adjusted by a predefined rotation speed. */
static void	rotate_player(t_player *player)
{
	if (player->rotating == ROT_RIGHT)
		player->heading += ROTATION_SPEED;
	else if (player->rotating == ROT_LEFT)
		player->heading -= ROTATION_SPEED;
	player->heading = angle_norm(player->heading);
}

/* Updates the player's position based on the calculated movement in the
   x and y directions. The player's new position is checked to ensure it
   does not collide with a wall (represented by '1' in the map). */
static void	move_player(t_map_data *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	int		map_grid_x;
	int		map_grid_y;

	new_x = game->player.x + move_x;
	new_y = game->player.y + move_y;
	map_grid_x = floor(new_x / TILE_SIZE);
	map_grid_y = floor(new_y / TILE_SIZE);
	if (game->map[map_grid_y][map_grid_x] == '1')
	{
		if (game->map[map_grid_y][(int)floor(game->player.x / TILE_SIZE)] == '1')
			new_y = game->player.y;
		if (game->map[(int)floor(game->player.y / TILE_SIZE)][map_grid_x] == '1')
			new_x = game->player.x;
	}
	game->player.x = new_x;
	game->player.y = new_y;
}

/* Handles player movement input when keys are pressed. Updates the player's
   movement state (moving forward, back, left, right, or rotating) based on
   the pressed keys. */
void	handle_movement_pressed(mlx_key_data_t keydata, t_map_data *game)
{
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) &&
		keydata.action == MLX_PRESS)
		game->player.moving_ahead = MOVE_FORWARD;
	else if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) && 
		(keydata.action == MLX_PRESS))
		game->player.moving_ahead = MOVE_BACK;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		game->player.moving_side = MOVE_LEFT;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		game->player.moving_side = MOVE_RIGHT;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game->player.rotating = ROT_LEFT;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game->player.rotating = ROT_RIGHT;
}

/* Handles player movement input when keys are released. Resets the player's
   movement state to stop when keys for movement or rotation are released. */
void	handle_movement_released(mlx_key_data_t keydata, t_map_data *game)
{
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S ||
		keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN) &&
		keydata.action == MLX_RELEASE)
		game->player.moving_ahead = MOVE_STOP;
	if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D) &&
		keydata.action == MLX_RELEASE)
		game->player.moving_side = MOVE_STOP;
	if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT) &&
		keydata.action == MLX_RELEASE)
		game->player.rotating = MOVE_STOP;
}