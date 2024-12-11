/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:44:21 by jbremser          #+#    #+#             */
/*   Updated: 2024/11/14 16:55:02 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include "libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define TILE_SIZE 30
# define MAP_WIDTH 10
# define MAP_HEIGHT 10
# define FOV_DEGREES 60
# define COLOR_FLOOR 0xB994702F
# define COLOR_CEILING 0x89CFF32F

typedef enum s_error_code
{
	EXIT_ARG_COUNT_ERROR = 200,
	EXIT_INVALID_ARGS = 201,
	EXIT_ARG_NAME_ERROR = 202,
	EXIT_MAP_INIT_ERROR = 203,
	EXIT_MAP_INIT_CALLOC_FAIL = 204,
	EXIT_FD_OPEN_ERROR = 205,
	EXIT_NO_MAP = 206, 
	EXIT_TEXTURE_LOAD_FAIL = 207,
	EXIT_PLAYER_SEARCH_FAIL = 208,
	EXIT_PARSE_COLOR_FAIL = 209
}	t_error;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	double	x;
	double	y;
	double	heading;
	float	fov_radians;
}	t_player;

typedef struct s_texture
{
	mlx_texture_t	*n;
	mlx_texture_t	*s;
	mlx_texture_t	*e;
	mlx_texture_t	*w;
	uint32_t		floor;
	uint32_t		ceiling;
}	t_texture;

typedef struct s_ray
{
	int			h_hit;
	float		angle_rad;
	double		distance;
	double		wall_h;
	double 		hit_part;
	uint32_t	x;
}	t_ray;

typedef struct s_map_data
{
	char    **info;
	int		rows;
	int		map_rows;
	int		map_cols;
	char	*floor_color;
	char	*ceiling_color;
	char	*n_wall_asset;
	char	*s_wall_asset;
	char	*e_wall_asset;
	char	*w_wall_asset;
	char	**map;
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_player	player;
	t_texture	textures;
}   t_map_data;

/* ************************************************************************** */
/*									error_handling							  */
/* ************************************************************************** */
int		handle_error(int errno, t_map_data *game);
void	clean_info_struct(t_map_data	*game);
void	free_game_struct(t_map_data	*game);

/* ************************************************************************** */
/*									map_init								  */
/* ************************************************************************** */
int	parse_args(char **argv, t_map_data	*game);

/* ************************************************************************** */
/*									raycasting								  */
/* ************************************************************************** */
t_vector	vec_new(double x, double y);
t_vector	vec_zero(void);
t_vector	vec_from_angle(float angle);
t_vector	vec_add(t_vector v1, t_vector v2);
t_vector	vec_sub(t_vector v1, t_vector v2);
t_vector	vec_mul(t_vector v, double n);
double		vec_len(t_vector v);
t_vector	vec_normalize(t_vector v);
double		vec_dot_product(t_vector v1, t_vector v2);
t_vector	vec_inverse(t_vector v);
int			vec_equal(t_vector v1, t_vector v2);
double		vec_angle(t_vector v);
t_vector	vec_rotate(t_vector v, int angle);
void		vec_print(t_vector v);
void		start_game(t_map_data *game);
int			init_game(t_map_data *game);
void 		raycasting(t_map_data *game);
void 		draw_column(t_map_data *game, t_ray *ray);
float		angle_norm(float angle);
uint32_t	get_tex_color(mlx_texture_t *tex, uint32_t x, uint32_t y);
void		set_image_color(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
uint32_t	rgba(int r, int g, int b, int a);
void		mlx_key(mlx_key_data_t keydata, void *param);
void		game_exit(t_map_data *game);
void		start_game(t_map_data *game);
void		game_loop(void *param);

#endif