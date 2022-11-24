/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:25:32 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/24 17:54:48 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall(double dir_x, double dir_y, t_global *glob, double mv_spd)
{
	int	i;

	i = 1;
	if (glob->scene->matrix_map[(int)(glob->wind->pos.x + dir_x * i * mv_spd)][(int)glob->wind->pos.y] == '1')
	{
		printf("Check(x): map[%d][%d] = %c\n",(int)(glob->wind->pos.x + dir_x * i * mv_spd), (int)glob->wind->pos.y, glob->scene->matrix_map[(int)(glob->wind->pos.x + dir_x * i * mv_spd)][(int)glob->wind->pos.y]);
		return (0);
	}
	if (glob->scene->matrix_map[(int)glob->wind->pos.x][(int)(glob->wind->pos.y + dir_y * i * mv_spd)] == '1')
	{
		printf("Check(y): map[%d][%d] = %c\n",(int)glob->wind->pos.x, (int)(glob->wind->pos.y + dir_y * i * mv_spd), glob->scene->matrix_map[(int)glob->wind->pos.x][(int)(glob->wind->pos.y + dir_y * i * mv_spd)]);
		return (0);
	}
	if (glob->scene->matrix_map[(int)(glob->wind->pos.x + dir_x * i * mv_spd)][(int)(glob->wind->pos.y + dir_y * i * mv_spd)] == '1')
	{
		printf("Check(x, y): map[%d][%d] = %c\n",(int)(glob->wind->pos.x + dir_x * i * mv_spd), (int)(glob->wind->pos.y + dir_y * i * mv_spd), glob->scene->matrix_map[(int)(glob->wind->pos.x + dir_x * i * mv_spd)][(int)(glob->wind->pos.y + dir_y * i * mv_spd)]);
		return (0);
	}
	return (1);
}

void	move(double dir_x, double dir_y, t_global *glob)
{
	double	mv_spd;

	mv_spd = MOV_SPD;
	if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_LEFT_SHIFT))
		mv_spd *= 2;
	if (check_wall(dir_x, dir_y, glob, mv_spd))
	{
		glob->wind->pos.x += dir_x * mv_spd;
		glob->wind->pos.y += dir_y * mv_spd;
	}	
}

void key_hook(mlx_key_data_t keycode, void *globb)
{
	t_global	*glob;

	glob = globb;
	printf("--initial stat:\n	pos(%f, %f)\n	dir(%f, %f)\n	plan(%f, %f)\n", glob->wind->pos.x, glob->wind->pos.y, glob->wind->dir.x, glob->wind->dir.y, glob->wind->plan.x, glob->wind->plan.y);
	if (keycode.key == MLX_KEY_W && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
	{
		move(glob->wind->dir.x, glob->wind->dir.y, glob);
	}
	if (keycode.key == MLX_KEY_S && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
	{
		move(-glob->wind->dir.x, -glob->wind->dir.y, glob);
	}
	if (keycode.key == MLX_KEY_A && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
	{
		move(-glob->wind->dir.y, glob->wind->dir.x, glob);
	}
	if (keycode.key == MLX_KEY_D && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
	{
		move(glob->wind->dir.y, -glob->wind->dir.x, glob);
	}
	if (keycode.key == MLX_KEY_LEFT)
	{
		double	old_dir_x = glob->wind->dir.x;
		glob->wind->dir.x = glob->wind->dir.x * cosf(0.05) - glob->wind->dir.y * sinf(0.05);
		glob->wind->dir.y = old_dir_x * sinf(0.05) + glob->wind->dir.y * cosf(0.05);
		double	old_plan_x = glob->wind->plan.x;
		glob->wind->plan.x = glob->wind->plan.x * cosf(0.05) - glob->wind->plan.y * sinf(0.05);
      	glob->wind->plan.y = glob->wind->plan.x * sinf(0.05) + glob->wind->plan.y * cosf(0.05);
		//mlx_mouse_move(glob->wind->win, width / 2, height / 2);
		//printf("pos(x, y)= %f, %f\ndir: %f, %f\n",  glob->wind->pos.x,  glob->wind->pos.y, glob->wind->dir.x, glob->wind->dir.y);
	}
	if (keycode.key == MLX_KEY_RIGHT)
	{
		double	old_dir_x = glob->wind->dir.x;
		glob->wind->dir.x = glob->wind->dir.x * cosf(-0.05) - glob->wind->dir.y * sinf(-0.05);
		glob->wind->dir.y = old_dir_x * sinf(-0.05) + glob->wind->dir.y * cosf(-0.05);
		double	old_plan_x = glob->wind->plan.x;
		glob->wind->plan.x = glob->wind->plan.x * cosf(-0.05) - glob->wind->plan.y * sinf(-0.05);
      	glob->wind->plan.y = glob->wind->plan.x * sinf(-0.05) + glob->wind->plan.y * cosf(-0.05);
	}
	//printf("keycode: %d\n", keycode.key);
    if (keycode.key == MLX_KEY_ESCAPE)
	{
		system("kill 0");
		free_glob(glob);
        mlx_terminate(glob->wind->mlx);
		free(glob->wind);
		exit (0);
	}
}