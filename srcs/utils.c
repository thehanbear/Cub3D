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

// static void	find_map_cols(t_map_data *game)
// {
// 	int x;
// 	int y;

// 	game->map_cols = 0;
// 	y = 0;
// 	while (y < game->map_rows)
// 	{
// 		x = 0;
// 		while (game->map[y][x])
// 			x++;
// 		if (x > game->map_cols )
// 			game->map_cols = x;
// 		y++;
// 	}
// }

static void	find_player_location(t_map_data *game, int *p_x, int *p_y)
{
	int	y;
	int	x;

	*p_x = -1;
	*p_y = -1;
	y = 0;
	while (y < game->map_rows)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'S')
			{
				*p_x = x;
				*p_y = y;
				return ;
			}	
			x++;
		}
		y++;
	}
}

void init_game(t_map_data *game)
{
	int	p_x;
	int p_y;

	// find_map_cols(game);
	find_player_location(game, &p_x, &p_y);
    game->player.x = p_x * TILE_SIZE + TILE_SIZE / 2;
    game->player.y = p_y * TILE_SIZE + TILE_SIZE / 2;
    game->player.fov_radians = (FOV_DEGREES * M_PI) / 180;
    game->player.heading = M_PI;
    game->mlx = NULL;
    game->image = NULL;
    game->textures.no = NULL;
    game->textures.ea = NULL;
    game->textures.so = NULL;
    game->textures.we = NULL;
}
