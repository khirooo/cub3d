/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:17:28 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/12 20:12:19 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
#include <string.h>
# include <limits.h>
#include <float.h>

#define width 512
#define height 512
typedef	struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef	struct s_scene
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		*f;
	int		*c;
	char	*str_map;
	char	**matrix_map;
}	t_scene;

typedef	struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;	
}	t_image;

typedef	struct s_window
{
	void	*mlx;
	void	*win;
	t_image	*image;
	t_point	pos;
	t_point	dir;
	t_point	plan;
		
}	t_window;

typedef	struct s_global
{
	t_window	*wind;
	t_scene		*scene;
} t_global;

void	print_err(char *err);
t_scene	*parse_scene_file(char	*file);
int		is_empty(char *line);
void	free_dp(char **i);
void	print_scene(t_scene *scene);
int		parse_map(t_scene *scene);
void	open_window(t_scene *scene);
#endif

