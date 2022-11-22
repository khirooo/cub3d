/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:25:32 by nkolle            #+#    #+#             */
/*   Updated: 2022/11/22 20:50:41 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    fck_norm(t_global *glob)
{
		glob->wind->pos.y += glob->wind->dir.y;
		glob->wind->pos.x += glob->wind->dir.x;
}

void    fck_norm1(t_global *glob)
{
		glob->wind->pos.y -= glob->wind->dir.y;
		glob->wind->pos.x -= glob->wind->dir.x;
}

int		get_dir(double x)
{
	if (x > 0)
	{
		if (x >= 0.5)
			return (1);
		return (0);
	}
	else
	{
		if (x <= -0.5)
			return (-1);
		return (0);
	}
}

int	check_wall(double dir_x, double dir_y, t_global *glob)
{
	int	i;

	i = 1;
	while (i < 3)
	{
		if (glob->scene->matrix_map[(int)(glob->wind->pos.x + dir_x * i * MOV_SPD)][(int)glob->wind->pos.y] == '1')
		{
			printf("Check(x): map[%d][%d] = %c\n",(int)(glob->wind->pos.x + dir_x * i * MOV_SPD), (int)glob->wind->pos.y, glob->scene->matrix_map[(int)(glob->wind->pos.x + dir_x * i * MOV_SPD)][(int)glob->wind->pos.y]);
			return (0);
		}
		if (glob->scene->matrix_map[(int)glob->wind->pos.x][(int)(glob->wind->pos.y + dir_y * i * MOV_SPD)] == '1')
		{
			printf("Check(y): map[%d][%d] = %c\n",(int)glob->wind->pos.x, (int)(glob->wind->pos.y + dir_y * i * MOV_SPD), glob->scene->matrix_map[(int)glob->wind->pos.x][(int)(glob->wind->pos.y + dir_y * i * MOV_SPD)]);
			return (0);
		}
		i++;
	}
	return (1);
}

void	move(double dir_x, double dir_y, t_global *glob)
{
	if (check_wall(dir_x, dir_y, glob))
	{
		if (mlx_is_key_down(glob->wind->mlx, MLX_KEY_LEFT_SHIFT))
		{
			glob->wind->pos.x += dir_x * 2 * MOV_SPD;
			glob->wind->pos.y += dir_y * 2 * MOV_SPD;
		}
		else
		{
			glob->wind->pos.x += dir_x * MOV_SPD;
			glob->wind->pos.y += dir_y * MOV_SPD;
		}
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
        exit(0);
}