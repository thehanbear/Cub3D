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

static int	find_player_location(t_map_data *game, int *p_x, int *p_y)
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
				return (1);
			}	
			x++;
		}
		y++;
	}
	return (0);
}

static void	trim_lb(char *str)
{
	str[ft_strlen(str) - 1] = '\0';
}

static int	load_textures(t_map_data *game)
{
	trim_lb(game->n_wall_asset);
	trim_lb(game->s_wall_asset);
	trim_lb(game->e_wall_asset);
	trim_lb(game->w_wall_asset);
	game->textures.n = mlx_load_png(game->n_wall_asset);
	if (!game->textures.n)
		return (0);
	game->textures.s = mlx_load_png(game->s_wall_asset);
	if (!game->textures.n)
		return (0);
	game->textures.e = mlx_load_png(game->e_wall_asset);
	if (!game->textures.n)
		return (0);
	game->textures.w = mlx_load_png(game->w_wall_asset);
	if (!game->textures.n)
		return (0);
	return (1);
}

int init_game(t_map_data *game)
{
	int	p_x;
	int p_y;

	// find_map_cols(game);
	if (find_player_location(game, &p_x, &p_y) == 0)
		return (EXIT_PLAYER_SEARCH_FAIL);
    game->player.x = p_x * TILE_SIZE + TILE_SIZE / 2;
    game->player.y = p_y * TILE_SIZE + TILE_SIZE / 2;
    game->player.fov_radians = (FOV_DEGREES * M_PI) / 180;
    game->player.heading = M_PI;
    game->mlx = NULL;
    game->image = NULL;
    if (load_textures(game) == 0)
		return (EXIT_TEXTURE_LOAD_FAIL);
	return(1);
}
