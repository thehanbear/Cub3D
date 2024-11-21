/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:17:14 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/11/15 01:17:46 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void init_player(t_map_data *game)
{
    game->player.x = game->p_x * TILE_SIZE + TILE_SIZE / 2;
    game->player.y = game->p_y * TILE_SIZE + TILE_SIZE / 2;
    game->player.fov_radians = (FOV_DEGREES * M_PI) / 180;
    game->player.heading = M_PI;
}

void init_game(t_map_data *game)
{
    game->p_y = 3;
    game->p_x = 14;
	game->w_map = 25;
	game->h_map = 9;
    game->map = calloc(10, sizeof(char *));
    game->map[0] = strdup("1111111111111111111111111");
    game->map[1] = strdup("1000000000000000000100001");
    game->map[2] = strdup("1001000000000P00000000001");
    game->map[3] = strdup("1001000000000000001000001");
    game->map[4] = strdup("1001000000000000001000001");
    game->map[5] = strdup("1001000000100000001000001");
    game->map[6] = strdup("1001000000000000001000001");
    game->map[7] = strdup("1001000000001000001000001");
    game->map[8] = strdup("1111111111111111111111111");
    game->map[9] = NULL;
    game->rows = MAP_HEIGHT;
    game->rows = MAP_WIDTH;
    game->mlx = NULL;
    game->image = NULL;
    game->textures.no = NULL;
    game->textures.ea = NULL;
    game->textures.so = NULL;
    game->textures.we = NULL;
}
