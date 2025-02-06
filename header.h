/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:44:21 by jbremser          #+#    #+#             */
/*   Updated: 2025/02/06 15:17:56 by jbremser         ###   ########.fr       */
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

# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 800
# define TILE_SIZE 30
# define FOV_DEGREES 60
# define ROTATION_SPEED .02
# define PLAYER_SPEED 1.5

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
	EXIT_PARSE_COLOR_FAIL = 209,
	EXIT_MINESWEEP_ERROR = 210,
	EXIT_NO_PLAYER = 211,
	EXIT_MLX_ERROR = 212,
	EXIT_EXTRA_ABC = 213,
	EXIT_NO_ASSETS = 214,
	EXIT_BAD_MAP = 215
}	t_error;

typedef enum s_movement_direction
{
	MOVE_STOP = 0,
	MOVE_FORWARD = 1,
	MOVE_BACK = 2,
	MOVE_LEFT = 3,
	MOVE_RIGHT = 4,
	ROT_LEFT = 5,
	ROT_RIGHT = 6
}	t_movement_direction;

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
	int		rotating;
	int		moving_ahead;
	int		moving_side;
}	t_player;

typedef struct s_keys
{
	int	move_forward;
	int	move_back;
	int	move_left;
	int	move_right;
	int	rotate_left;
	int	rotate_right;
}	t_keys;

typedef struct s_texture
{
	mlx_texture_t	*n;
	mlx_texture_t	*s;
	mlx_texture_t	*e;
	mlx_texture_t	*w;
	uint32_t		floor;
	uint32_t		ceiling;
}	t_texture;

typedef struct s_camera
{
	double	fov_radians;
	double	focal_length;
	double	angle_increment;
}	t_camera;

typedef struct s_ray
{
	int			h_hit;
	float		angle_rad;
	double		distance;
	double		wall_h;
	double		hit_part;
	uint32_t	x;
}	t_ray;

typedef struct s_map_data
{
	int			temp_x;
	int			temp_y;
	int			temp_a;
	t_vector	step;
	t_vector	vector_player;
	char		**info;
	int			rows;
	int			map_rows;
	int			map_cols;
	char		*floor_color;
	char		*ceiling_color;
	char		*n_wall_asset;
	char		*s_wall_asset;
	char		*e_wall_asset;
	char		*w_wall_asset;
	char		**map;
	char		**copy;
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_player	player;
	t_player	temp_player;
	t_keys		keys_pressed;
	t_texture	textures;
	t_camera	camera;
}	t_map_data;

/* ************************************************************************** */
/*									coloring								  */
/* ************************************************************************** */
uint32_t	get_tex_col(mlx_texture_t *tex, uint32_t x, uint32_t y);
void		set_img_col(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t col);
uint32_t	rgba(int r, int g, int b, int a);

/* ************************************************************************** */
/*									error_handling							  */
/* ************************************************************************** */
int			handle_error(int errno, t_map_data *game);
void		clean_info_struct(t_map_data *game);
void		free_game_struct(t_map_data	*game);
void		free_array(char **str);

/* ************************************************************************** */
/*									find_functions							  */
/* ************************************************************************** */
int			find_player(t_map_data	*game, int x, int y, int P_found);
void		find_map(t_map_data	*game);

/* ************************************************************************** */
/*									minesweep								  */
/* ************************************************************************** */
int			minesweep(t_map_data *game);
int			check_line(char *line);
int			check_info(t_map_data *game);

/* ************************************************************************** */
/*									mlx_execution							  */
/* ************************************************************************** */
void		game_loop(void *param);
int			start_game(t_map_data *game);
void		mlx_key(mlx_key_data_t keydata, void *param);
void		mlx_clean(t_map_data *game);

/* ************************************************************************** */
/*									movement								  */
/* ************************************************************************** */
void		player_loop(void *param);
void		handle_movement_pressed(mlx_key_data_t keydata, t_map_data *game);
void		handle_movement_released(mlx_key_data_t keydata, t_map_data *game);

/* ************************************************************************** */
/*									parse_args								  */
/* ************************************************************************** */
int			parse_args(char **argv, t_map_data	*game);

/* ************************************************************************** */
/*									raycasting								  */
/* ************************************************************************** */
void		raycasting(t_map_data *game);

/* ************************************************************************** */
/*									rendering								  */
/* ************************************************************************** */
void		draw_column(t_map_data *game, t_ray *ray);
void		draw_wall_bg(t_map_data *game, t_ray *ray, mlx_texture_t *hit_text);

/* ************************************************************************** */
/*									utils_movements							  */
/* ************************************************************************** */
double		set_move_heading_x(t_map_data	*game, double move_x);
double		set_move_heading_y(t_map_data	*game, double move_y);
int			find_extras(char **map);
int			check_temp(char **temp, int i);
int			check_color(char *str);

/* ************************************************************************** */
/*									utils_raycasting						  */
/* ************************************************************************** */
float		angle_norm(float angle);
int			y_r(float angle);
int			x_r(float angle);
int			check_wall(float x, float y, t_map_data *game);

/* ************************************************************************** */
/*									utils									  */
/* ************************************************************************** */
int			init_game(t_map_data *game);
void		set_heading(t_map_data	*game, int y, int x);

/* ************************************************************************** */
/*										vector_init							  */
/* ************************************************************************** */
t_vector	vec_new(double x, double y);
t_vector	vec_from_angle(float angle);

/* ************************************************************************** */
/*										vector_utils						  */
/* ************************************************************************** */
t_vector	vec_add(t_vector v1, t_vector v2);
t_vector	vec_sub(t_vector v1, t_vector v2);
t_vector	vec_mul(t_vector v, double n);
double		vec_len(t_vector v);

#endif