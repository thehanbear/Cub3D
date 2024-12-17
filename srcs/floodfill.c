/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:13:10 by jbremser          #+#    #+#             */
/*   Updated: 2024/12/17 16:21:59 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_player	*check_copy(t_map_data *game)
{
	int	x;
	int	y;
	// t_player *temp;

	// temp = NULL;
	x = 0;
	y = 0;
	while (game->copy[y])
	{
		while (game->copy[y][x])
		{
			if (game->copy[y][x] == '0')
			{
			// || game->copy[y][x] == 'C' || game->copy[y][x] == 'P')
			printf("\ncheck_copy fail\n");
			// temp->y = y;
			// temp->x = x;
			return (NULL);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (&game->player);
}

static char	**map_copy(t_map_data *game)
{
	int	y;

	y = 0;
	game->copy = malloc(sizeof(char *) * (game->rows + 1));
	if (!game->copy)
		return (NULL);
	while (game->map[y])
	{
		game->copy[y] = ft_strdup(game->map[y]);
		y++;
	}
	game->copy[y] = NULL;
	printf("!game->copy:");
	print_map(game->copy);
	return (game->copy);
}

static void	fill(t_map_data *game, int y, int x)
{
	printf("\n!inside fill!\n");
	if (game->copy[y][x] == '1' || game->copy[y][x] == 'F')
		return ;
	else
		game->copy[y][x] = 'F';
	fill(game, y + 1, x);
	fill(game, y - 1, x);
	fill(game, y, x + 1);
	fill(game, y, x - 1);
	// if (check_copy(game) != &game->player)
	// 	fill(game);

	printf("one fill down\n");
	// print_map(game->copy);

}




int full_flood_fill(t_map_data *game, t_player fill_pos)
{
	// t_player curr_pos;
	printf("b4 full_floodfill\n");

	game->copy = map_copy(game);
	if (!game->copy)
		return (1); 
	printf("after map_copy\n");
	
	fill(game, (int)fill_pos.y, (int)fill_pos.x);
	printf("after fill\n");
	// if (check_copy(game) == &game->player)
	// 	printf("full_floodfill\n");
	return (0);
}
