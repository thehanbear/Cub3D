/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:11:15 by jbremser          #+#    #+#             */
/*   Updated: 2024/12/19 14:33:56 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void		find_map(t_map_data	*game);
char		*find_asset(t_map_data	*game, char	*arg);
int 		find_no_map(t_map_data *game);
void 		find_ones(t_map_data *game);
int			find_player(t_map_data	*game);

void	find_map(t_map_data	*game)
{
	game->n_wall_asset = find_asset(game, "NO ");
	game->s_wall_asset = find_asset(game, "SO ");
	game->w_wall_asset = find_asset(game, "WE ");
	game->e_wall_asset = find_asset(game, "EA ");
	game->floor_color = find_asset(game, "F ");
	game->ceiling_color = find_asset(game, "C ");
	find_ones(game);
	// print_info(game);
}

char	*find_asset(t_map_data	*game, char	*arg)
{
	int y = 0;
	int x = 0;

	while (game->info[y])
	{
		if (!ft_strncmp(&game->info[y][x], arg, ft_strlen(arg)))
		{
			x = ft_strlen(arg) - 1;
			while(!ft_strncmp(&game->info[y][x], " ", 1))
				x++;
			return (ft_strdup(&game->info[y][x]));
		}
		y++;
	}
	return (NULL);
}

int find_no_map(t_map_data *game)
{
    int y = 0;
    int x = 0;

    while (game->info[y])
    {
        x = 0;
        while (game->info[y][x] == ' ')
            x++;
        if (game->info[y][x] == '1')
            return (0);
        y++;
    }
    return (1);
}

void find_ones(t_map_data *game)
{
    int y = 0;
    int a = 0;
    int x = 0;
	if (find_no_map(game))
		handle_error(EXIT_NO_MAP, game);
    while (y < game->rows && game->info[y])
    {
        x = 0;
        while (game->info[y][x] && game->info[y][x] == ' ')
            x++;
		game->map_rows = game->rows - y + 1;
        if (game->info[y][x] && game->info[y][x] == '1')
        {
            game->map = (char **)ft_calloc((game->rows - y + 1), sizeof(char *));
            if (!game->map)
                handle_error(EXIT_MAP_INIT_CALLOC_FAIL, game);
            while (game->info[y])
            {
                game->map[a] = ft_strdup(game->info[y]);
				a++;
                y++;
            }
        }
        y++;
    }
} 


int	find_player(t_map_data	*game)
{
	int	x;
	int	y;
	int P_found;

	P_found = 0;
	x = 0;
	y = 0;
	while (game->map[y])
	{
		while (game->map[y][x])
		{
			if (ft_strchr("NSWE", game->map[y][x]))
			{
				if (game->map[y][x] == 'N')
					game->player.heading = 3 * M_PI / 2;
				if (game->map[y][x] == 'E')
					game->player.heading = 0;
				if (game->map[y][x] == 'S')
					game->player.heading = M_PI / 2;
				if (game->map[y][x] == 'W')
					game->player.heading = M_PI;
				// || game->copy[y][x] == 'C' || game->copy[y][x] == 'P')
				// printf("");
				game->player.y = y;
				game->player.x = x;
				game->map[y][x] = '0';
				printf("\nfind_player:\nplayer pos: %d,%d\nplayer heading: %d\n", (int)game->player.y, (int)game->player.x, (int)game->player.heading);
				P_found++;
				// print_map(game->map);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (P_found);

}
