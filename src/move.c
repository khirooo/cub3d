/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:25:32 by nkolle            #+#    #+#             */
/*   Updated: 2022/12/05 17:08:17 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall(t_point dir, char **matrix_map, t_point pos, double mv_spd)
{
	int	i;

	i = 1;
	if (matrix_map[(int)(pos.x + dir.x * i * mv_spd)][(int)pos.y] == '1')
		return (1);
	if (matrix_map[(int)pos.x][(int)(pos.y + dir.y * i * mv_spd)] == '1')
		return (2);
	if (matrix_map[(int)(pos.x + dir.x * i * mv_spd)][(int)(pos.y + dir.y * i
			* mv_spd)] == '1')
		return (3);
	return (0);
}

int	check_for_wall(char **matrix_map, t_ray *ray)
{
	if (ray->sidedist.x < ray->sidedist.y)
	{
		ray->sidedist.x += ray->dist.x;
		ray->sqr_map.x += (int)ray->step.x;
		ray->side = 0;
	}
	else
	{
		ray->sidedist.y += ray->dist.y;
		ray->sqr_map.y += (int)ray->step.y;
		ray->side = 1;
	}
	if (matrix_map[(int)ray->sqr_map.x][(int)ray->sqr_map.y] == '1')
		return (1);
	return (0);
}

void	move(double dir_x, double dir_y, t_global *gl)
{
	double	sp;
	t_point	dir;

	dir.x = dir_x;
	dir.y = dir_y;
	sp = MOV_SPD;
	if (mlx_is_key_down(gl->wind->mlx, MLX_KEY_LEFT_SHIFT))
		sp *= 2;
	if (!check_wall(dir, gl->scene->matrix_map, gl->wind->pos, sp))
	{
		gl->wind->pos.x += dir_x * sp;
		gl->wind->pos.y += dir_y * sp;
	}
	else if ((check_wall(dir, gl->scene->matrix_map, gl->wind->pos, sp) == 1) \
			&& (gl->scene->matrix_map[(int)gl->wind->pos.x] \
				[(int)(gl->wind->pos.y + dir.y * sp)] != '1'))
			gl->wind->pos.y += dir_y * sp;
	else if ((check_wall(dir, gl->scene->matrix_map, gl->wind->pos, sp) == 2) \
			&& (gl->scene->matrix_map[(int)(gl->wind->pos.x + dir.x * sp)] \
				[(int)gl->wind->pos.y] != '1'))
		gl->wind->pos.x += dir_x * sp;
}

void	key_move(t_global *glob)
{
	if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_W))
		move(glob->wind->dir.x, glob->wind->dir.y, glob);
	if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_S))
		move(-glob->wind->dir.x, -glob->wind->dir.y, glob);
	if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_A))
		move(-glob->wind->dir.y, glob->wind->dir.x, glob);
	if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_D))
		move(glob->wind->dir.y, -glob->wind->dir.x, glob);
	if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_LEFT))
		mouse_rotate(glob->wind, 0, 0);
	if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_RIGHT))
		mouse_rotate(glob->wind, WIDTH, 0);
}

void	key_hook(mlx_key_data_t keycode, void *globb)
{
	t_global	*glob;

	glob = globb;
	if (keycode.key == MLX_KEY_ESCAPE)
	{
		system("kill 0");
		free_glob(glob);
		mlx_terminate(glob->wind->mlx);
		free(glob->wind);
		exit(0);
	}
}
