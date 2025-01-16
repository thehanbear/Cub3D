/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:19:41 by hlee-sun          #+#    #+#             */
/*   Updated: 2025/01/16 17:16:55 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	game_loop(void *param);
void	start_game(t_map_data *game);
void	game_exit(t_map_data *game);
void	mlx_key(mlx_key_data_t keydata, void *param);

/* Main game loop function that is repeatedly called during the game.
   It deletes the previous image, creates a new image, performs raycasting,
   and renders the image to the window. */
// TODO add freeing of memory before exit
void	game_loop(void *param)
{
	t_map_data	*game;

	game = param;
	if (game->image != NULL)
		mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->image)
	{
		printf("Failed to create new image\n");
		exit(1);
	}
	raycasting(game);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}

/* Initializes the game window using the mlx library, sets up the game
   loop, key hook, and player loop, and starts the mlx event loop. */
void	start_game(t_map_data *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", 0);
	if (!game->mlx)
	{
		printf("Failed to initialize mlx\n");
		exit(1);
	}
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop_hook(game->mlx, &player_loop, game);
	mlx_key_hook(game->mlx, &mlx_key, game);
	if (game->mlx == NULL)
	{
		printf("\nmlx is NULL\n");
		game_exit(game);
	}
	mlx_loop(game->mlx);
}

/* Cleans up the game resources, deletes the image, and terminates the mlx
   library before exiting the program. */
void	game_exit(t_map_data *game)
{
	if (game->image != NULL)
	{
		mlx_delete_image(game->mlx, game->image);
	}
	if (game->mlx != NULL)
	{
		mlx_terminate(game->mlx);
	}
	exit(0);
}

/* Handles key events for the game. Specifically checks for the escape key
   to exit the game and handles movement actions based on key presses and
   releases. */
void	mlx_key(mlx_key_data_t keydata, void *param)
{
	t_map_data	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game_exit(game);
	else
	{
		handle_movement_pressed(keydata, game);
		handle_movement_released(keydata, game);
	}
}
