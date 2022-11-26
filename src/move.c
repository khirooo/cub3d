/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:25:32 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/26 18:34:06 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall(t_point dir, char **matrix_map, t_point pos, double mv_spd)
{
	int	i;

	i = 1;
	if (matrix_map[(int)(pos.x + dir.x * i * mv_spd)][(int)pos.y] == '1')
		return (0);
	if (matrix_map[(int)pos.x][(int)(pos.y + dir.y * i * mv_spd)] == '1')
		return (0);
	if (matrix_map[(int)(pos.x + dir.x * i * mv_spd)][(int)(pos.y + dir.y \
		* i * mv_spd)] == '1')
		return (0);
	return (1);
}

void	move(double dir_x, double dir_y, t_global *glob)
{
	double	mv_spd;
	t_point	dir;

	dir.x = dir_x;
	dir.y = dir_y;
	mv_spd = MOV_SPD;
	if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_LEFT_SHIFT))
		mv_spd *= 2;
	if (check_wall(dir, glob->scene->matrix_map, glob->wind->pos, mv_spd))
	{
		glob->wind->pos.x += dir_x * mv_spd;
		glob->wind->pos.y += dir_y * mv_spd;
	}	
}

void key_hook(mlx_key_data_t keycode, void *globb)
{
	t_global	*glob;

	glob = globb;
    if (keycode.key == MLX_KEY_ESCAPE)
	{
		system("kill 0");
		free_glob(glob);
        mlx_terminate(glob->wind->mlx);
		free(glob->wind);
		exit (0);
	}
}