/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:47:08 by jbremser          #+#    #+#             */
/*   Updated: 2025/01/22 18:27:22 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

double	set_move_heading_x(t_map_data	*game, double move_x);
double	set_move_heading_y(t_map_data	*game, double move_y);
int		find_extras(char **map);
int		check_temp(char **temp, int i);
int		check_color(char *str);

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

int	find_extras(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (ft_isalpha(map[y][x]) && !(ft_strchr("NSWE", map[y][x])))
				return (1);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int	check_color(char *str)
{
	int		len;
	int		i;
	char	**temp;

	len = ft_strlen(str);
	if (len < 5)
		return (1);
	i = 0;
	temp = ft_split(str, ',');
	if (!temp)
	{
		free_array(temp);
		return (1);
	}
	while (temp[i])
		i++;
	if (i != 3)
	{
		free_array(temp);
		return (1);
	}
	return (check_temp(temp, i));
}

// bool	check_empty_string(char *temp)
// {
// 	while (temp)
// 	{
// 		if (ft_strcmp(temp, " ") || ft_strcmp(temp, "\t"))
// 			temp++;
// 		else
// 			return (1);
// 	}
// 	return(0);
// }

int	check_temp(char	**temp, int i)
{
	int	x;
	int	temp_n;
		
	x = 0;
	while (x < i)
	{
		temp_n = -1;
		// printf("temp[x]:%s\n", temp[x]);
		// if (ft_isprint(temp[x]))
		temp_n = ft_atoi(temp[x]);
		// printf("temp_n:%d\n", temp_n);
		// if (check_empty_string(temp[x]))
		// {
		// 	printf("color value is empty: %s\n", temp[x]);
		// 	free_array(temp);
		// 	return (1);
		// }

		if (temp_n < 0 || temp_n > 255)
		{
			printf("1:RBG values must be between 0-255: %d\n", temp_n);
			free_array(temp);
			return (1);
		}
		// if (!ft_atoi(temp[x]))
		// {
		// 	printf("2:RBG values must be between 0-255: %s\n", temp[x]);
		// 	free_array(temp);
		// 	return (1);
		// }
		else
			x++;
	}
	if (temp)
		free_array(temp);
	return (0);
}
