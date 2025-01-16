/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:00:30 by jbremser          #+#    #+#             */
/*   Updated: 2025/01/16 17:07:34 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void		free_array(char **str);
int			handle_error(int errno, t_map_data *game);
void		free_string(char *str);
void		free_game_struct(t_map_data	*game);
static void	map_free_error(int errno, t_map_data *game);

/* Frees each string in the array `str` and then frees the array itself. */
void	free_array(char **str)
{
	int	y;

	y = 0;
	while (str[y])
		free(str[y++]);
	free(str);
}

/* Frees the memory allocated for the string `str` if it's not NULL. */
void	free_string(char *str)
{
	if (str)
		free(str);
}

/* Frees various dynamically allocated memory within the `game` structure,
   including the map, wall assets, and color strings. Then frees the `game`
   structure itself. */
void	free_game_struct(t_map_data	*game)
{
	if (game->map)
		free_array(game->map);
	free_string(game->n_wall_asset);
	free_string(game->s_wall_asset);
	free_string(game->e_wall_asset);
	free_string(game->w_wall_asset);
	free_string(game->ceiling_color);
	free_string(game->floor_color);
	if (game)
		free(game);
}

/* Prints an error message based on the provided error code (`errno`), then
   frees any allocated memory related to the `game` structure and exits the
   program with a failure code. */
static void	map_free_error(int errno, t_map_data	*game)
{
	if (errno == EXIT_MAP_INIT_CALLOC_FAIL)
		printf("Error: Calloc fail\n");
	if (errno == EXIT_FD_OPEN_ERROR)
		printf("FD NO OPEN!\n");
	if (errno == EXIT_NO_MAP)
		printf("WHERE MAP!\n");
	if (errno == EXIT_TEXTURE_LOAD_FAIL)
		printf("Texture loading failed\n");
	if (errno == EXIT_PLAYER_SEARCH_FAIL)
		printf("Failed to find player on map\n");
	if (errno == EXIT_PARSE_COLOR_FAIL)
		printf("Failed to parse floor or ceiling color\n");
	if (errno == EXIT_MINESWEEP_ERROR)
		printf("Minesweep failed: open area on map\n");
	if (errno == EXIT_NO_PLAYER)
		printf("Invalid amount of Player(s) found on map\n");
	if (game)
		free_game_struct(game);
	exit(2);
}

/* Handles different types of errors based on the provided `errno`. Prints
   appropriate error messages and calls `map_free_error` for critical errors
   that require cleanup, or returns an error code based on the `errno`. */
int	handle_error(int errno, t_map_data *game)
{
	if (errno == EXIT_ARG_COUNT_ERROR)
		write(2, "Invalid amount of Args\n", 24);
	if (errno == EXIT_INVALID_ARGS)
		write(2, "Invalid Arguments\n", 19);
	if (errno == EXIT_ARG_NAME_ERROR)
		write(2, "Invalid File Names\n", 20);
	if (errno == EXIT_MAP_INIT_CALLOC_FAIL || errno == EXIT_FD_OPEN_ERROR
		|| errno == EXIT_MAP_INIT_ERROR || errno == EXIT_NO_MAP
		|| errno == EXIT_TEXTURE_LOAD_FAIL
		|| errno == EXIT_PLAYER_SEARCH_FAIL || errno == EXIT_PARSE_COLOR_FAIL
		|| errno == EXIT_MINESWEEP_ERROR || errno == EXIT_NO_PLAYER)
		map_free_error(errno, game);
	if (errno == 0)
		return (0);
	else
		return (1);
}
