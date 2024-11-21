/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:19:41 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/11/15 04:37:19 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void game_loop(void *param)
{
    t_game *game = param;

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

void start_game(t_game *game)
{
    game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", 0);
	if (!game->mlx) 
	{
       printf("Failed to initialize mlx\n");
        exit(1);
    }
    init_player(game);
    mlx_loop_hook(game->mlx, &game_loop, game);
    mlx_key_hook(game->mlx, &mlx_key, game);
    mlx_loop(game->mlx);
}

void game_exit(t_game *game)
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

void mlx_key(mlx_key_data_t keydata, void *param)
{
    t_game *game;

    game = param;
    if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) 
    {
        game_exit(game);
    }
}

