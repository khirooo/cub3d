/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:17:28 by kfergani          #+#    #+#             */
/*   Updated: 2022/12/05 19:48:26 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <limits.h>
# include <float.h>
# include <time.h>
# include <stdint.h>

# define WIDTH 1000
# define HEIGHT 1000
# define MOV_SPD 0.1
# define KEY_A 0
# define KEY_D 2
# define KEY_W 13
# define KEY_S 1
# define KEY_LEFT 123
# define KEY_ESC 53
# define KEY_ESC 53

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_d_point
{
	int	x;
	int	y;
}	t_d_point;

typedef struct s_vline
{
	int			height;
	int			start;
	int			end;
	t_d_point	tex;
}	t_vline;

typedef struct s_scene
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				*f;
	int				*c;
	char			*str_map;
	mlx_texture_t	**text_arr;
	char			**matrix_map;
}	t_scene;

typedef struct s_ray
{
	t_point	cam;
	t_point	dir;
	t_point	sqr_map;
	t_point	step;
	t_point	sidedist;
	t_point	dist;
	int		side;
	double	perpwalldist;
	double	wall_x;
}	t_ray;

typedef struct s_window
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_point		pos;
	t_point		dir;
	t_point		plan;
	int			x;
}	t_window;

typedef struct s_global
{
	t_window	*wind;
	t_scene		*scene;
	int			buffer[WIDTH][HEIGHT];
	int			mode;
}	t_global;

void	print_err(char *err);
t_scene	*parse_scene_file(char	*file);
int		is_empty(char *line);
void	free_dp(char **i);
void	print_scene(t_scene *scene);
int		parse_map(t_scene *scene);
void	open_window(t_scene *scene);
void	key_hook(mlx_key_data_t keycode, void *glob);
void	raycast(void *globb);
void	set_pos_dir(t_scene *scene, t_window *wind);
void	free_glob(t_global *glob);
int		get_rgba(int r, int g, int b, int a);
void	play_music(void);
void	mouse_rotate(t_window *wind, int a, int flag);
void	move(double dir_x, double dir_y, t_global *glob);
void	set_dir(t_window *wind, char c);
void	set_plan(t_window *wind, char c);
void	set_pos_dir(t_scene *scene, t_window *wind);
void	draw_buff(t_global *glob, int32_t buffer[WIDTH][HEIGHT]);
int		check_for_wall(char **matrix_map, t_ray *ray);
void	key_move(t_global *glob);
int		get_pixel_color(mlx_texture_t *tex, t_vline *line);
void	mouse_rotate(t_window *wind, int a, int flag);
int		*get_rgb(char *line);
int		add_to_map(t_scene *scene, char *line);
void	load_textures(t_scene *scene);
int		init_scene(t_scene **scene);
void	switch_scene(t_global *glob);
#endif
